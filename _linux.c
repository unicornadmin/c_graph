#include <errno.h> 
#include <signal.h>
#include <linux/vt.h>
#include <linux/kd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

#ifndef Bool
#define Bool int
#endif

#define ErrorF(str)

int  LinuxConsoleFd;
static int  vtno;
static int  activeVT;
static Bool enabled;

void LinuxFini (void);

void PlatformFini()
{
    LCDFini();
    //KeyboardFini();
    LinuxFini();
}

/* Check before chowning -- this avoids touching the file system */
static void LinuxCheckChown (char *file)
{
    struct stat	    st;
    __uid_t	    u;
    __gid_t	    g;

    if (stat (file, &st) < 0)
	return;
    u = getuid ();
    g = getgid ();
    if (st.st_uid != u || st.st_gid != g)
	chown (file, u, g);
}

static void LinuxEnable (void)
{
    struct sigaction	act;
    struct vt_mode	VT;
    
    if (enabled)
	return;
    /*
     * now get the VT
     */
    if (ioctl(LinuxConsoleFd, VT_ACTIVATE, vtno) != 0)
	ErrorF("LinuxInit: VT_ACTIVATE failed\n");
    if (ioctl(LinuxConsoleFd, VT_WAITACTIVE, vtno) != 0)
	ErrorF("LinuxInit: VT_WAITACTIVE failed\n");
    if (ioctl(LinuxConsoleFd, VT_GETMODE, &VT) < 0)
	exit(-1);
    if (ioctl(LinuxConsoleFd, KDSETMODE, KD_GRAPHICS) < 0)
	exit(-1);
  
    VT.mode = VT_PROCESS;

    if (ioctl(LinuxConsoleFd, VT_SETMODE, &VT) < 0) 
	exit(-1);

    enabled = TRUE;
}

static void LinuxDisable (void)
{
    ioctl (LinuxConsoleFd, VT_RELDISP, 1);
}



static void fatalerr(int sig)
{
    PlatformFini();
}

int LinuxInit (void)
{
    int i, fd;
    char vtname[11];
    struct vt_stat vts;
    struct stat	statb;

    signal(9 , fatalerr); /* SIGKILL */
    signal(15, fatalerr); /* SIGTERM */
    signal(11, fatalerr); /* SIGSEGV */
    signal(7 , fatalerr); /* SIGBUS */
    signal(13, fatalerr); /* SIGPIPE */

    LinuxConsoleFd = -1;
    /* check if we're run with euid==0 */
    if (geteuid() != 0)
	exit(-1);

    if ((fd = open("/dev/tty0",O_WRONLY,0)) < 0)
	exit(-1);
    if ((ioctl(fd, VT_OPENQRY, &vtno) < 0) || (vtno == -1))
	exit(-1);

    close(fd);

    sprintf(vtname,"/dev/tty%d",vtno); /* /dev/tty1-64 */

    if ((LinuxConsoleFd = open(vtname, O_RDWR|O_NDELAY, 0)) < 0)
	exit(-1);
    
    /* change ownership of the vt */
    LinuxCheckChown (vtname);

    /*
     * the current VT device we're running on is not "console", we want
     * to grab all consoles too
     *
     * Why is this needed?
     */
    LinuxCheckChown ("/dev/tty0");
    /*
     * Linux doesn't switch to an active vt after the last close of a vt,
     * so we do this ourselves by remembering which is active now.
     */
    if (ioctl(LinuxConsoleFd, VT_GETSTATE, &vts) == 0)
	activeVT = vts.v_active;
    LinuxEnable();

    return 1;
}




void LinuxFini (void)
{
    struct vt_mode   VT;
    struct vt_stat  vts;
    int		    fd;

    LinuxDisable();

    if (LinuxConsoleFd < 0)
	return;

    if (ioctl(LinuxConsoleFd, VT_GETMODE, &VT) != -1) {
	VT.mode = VT_AUTO;
	ioctl(LinuxConsoleFd, VT_SETMODE, &VT); /* set dflt vt handling */
    }
    ioctl(LinuxConsoleFd, KDSETMODE, KD_TEXT);

    ioctl (LinuxConsoleFd, VT_GETSTATE, &vts);
    /*
     * Find a legal VT to switch to, either the one we started from
     * or the lowest active one that isn't ours
     */
    if (activeVT < 0 || 
	activeVT == vts.v_active || 
	!(vts.v_state & (1 << activeVT))) {
	for (activeVT = 1; activeVT < 16; activeVT++)
	    if (activeVT != vtno && (vts.v_state & (1 << activeVT)))
		break;
	if (activeVT == 16)
	    activeVT = -1;
    }
    /*
     * Perform a switch back to the active VT when we were started
     */
    if (activeVT >= -1) {
	ioctl (LinuxConsoleFd, VT_ACTIVATE, activeVT);
	ioctl (LinuxConsoleFd, VT_WAITACTIVE, activeVT);
	activeVT = -1;
    }
    close(LinuxConsoleFd);                /* make the vt-manager happy */
    fd = open ("/dev/tty0", O_RDWR|O_NDELAY, 0);
    if (fd >= 0) {
	ioctl (fd, VT_GETSTATE, &vts);
	if (ioctl (fd, VT_DISALLOCATE, vtno) < 0)
	    fprintf (stderr, "Can't deallocate console %d errno %d\n",
		     vtno, errno);
	close (fd);
    }
    return;
}
