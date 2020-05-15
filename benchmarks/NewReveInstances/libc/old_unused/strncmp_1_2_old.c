/* glibc */
#include <stddef.h>

extern int __mark(int);
int
strncmp (const char *s1, const char *s2, size_t n)
{
  unsigned char c1 = '\0';
  unsigned char c2 = '\0';

  while (n > 0)
    {
      c1 = (unsigned char) *s1++;
      c2 = (unsigned char) *s2++;
      if (c1 == '\0' || c1 != c2)
          return c1 - c2;
      n--;
      __mark(42);
    }

  return c1 - c2;
}


// SPDX-License-Identifier: GPL-2.0
/* -*-linux-c-*-
 * vendor-specific code for SCSI CD-ROM's goes here.
 *
 * This is needed becauce most of the new features (multisession and
 * the like) are too new to be included into the SCSI-II standard (to
 * be exact: there is'nt anything in my draft copy).
 *
 * Aug 1997: Ha! Got a SCSI-3 cdrom spec across my fingers. SCSI-3 does
 *           multisession using the READ TOC command (like SONY).
 *
 *           Rearranged stuff here: SCSI-3 is included allways, support
 *           for NEC/TOSHIBA/HP commands is optional.
 *
 *   Gerd Knorr <kraxel@cs.tu-berlin.de> 
 *
 * --------------------------------------------------------------------------
 *
 * support for XA/multisession-CD's
 * 
 *   - NEC:     Detection and support of multisession CD's.
 *     
 *   - TOSHIBA: Detection and support of multisession CD's.
 *              Some XA-Sector tweaking, required for older drives.
 *
 *   - SONY:    Detection and support of multisession CD's.
 *              added by Thomas Quinot <thomas@cuivre.freenix.fr>
 *
 *   - PIONEER, HITACHI, PLEXTOR, MATSHITA, TEAC, PHILIPS: known to
 *              work with SONY (SCSI3 now)  code.
 *
 *   - HP:      Much like SONY, but a little different... (Thomas)
 *              HP-Writers only ??? Maybe other CD-Writers work with this too ?
 *              HP 6020 writers now supported.
 */

#include <linux/cdrom.h>
#include <linux/errno.h>
#include <linux/string.h>
//#include <linux/bcd.h>
//#include <linux/blkdev.h>
//#include <linux/slab.h>

#include <scsi/scsi.h>
//#include <scsi/scsi_cmnd.h>
//#include <scsi/scsi_device.h>
//#include <scsi/scsi_host.h>
#include <scsi/scsi_ioctl.h>

#include "sr.h"

#if 0
#define DEBUG
#endif

/* here are some constants to sort the vendors into groups */

#define VENDOR_SCSI3           1	/* default: scsi-3 mmc */

#define VENDOR_NEC             2
#define VENDOR_TOSHIBA         3
#define VENDOR_WRITER          4	/* pre-scsi3 writers */
#define VENDOR_CYGNAL_85ED     5	/* CD-on-a-chip */

#define VENDOR_TIMEOUT	30*HZ

void sr_vendor_init(Scsi_CD *cd)
{
	const char *vendor = cd->device->vendor;
	const char *model = cd->device->model;
	
	/* default */
	cd->vendor = VENDOR_SCSI3;
	if (cd->readcd_known)
		/* this is true for scsi3/mmc drives - no more checks */
		return;

	if (cd->device->type == TYPE_WORM) {
		cd->vendor = VENDOR_WRITER;

	} else if (!strncmp(vendor, "NEC", 3)) {
		cd->vendor = VENDOR_NEC;
		if (!strncmp(model, "CD-ROM DRIVE:25", 15) ||
		    !strncmp(model, "CD-ROM DRIVE:36", 15) ||
		    !strncmp(model, "CD-ROM DRIVE:83", 15) ||
		    !strncmp(model, "CD-ROM DRIVE:84 ", 16)
#if 0
		/* my NEC 3x returns the read-raw data if a read-raw
		   is followed by a read for the same sector - aeb */
		    || !strncmp(model, "CD-ROM DRIVE:500", 16)
#endif
		    )
			/* these can't handle multisession, may hang */
			cd->cdi.mask |= CDC_MULTI_SESSION;

	} else if (!strncmp(vendor, "TOSHIBA", 7)) {
		cd->vendor = VENDOR_TOSHIBA;

	} else if (!strncmp(vendor, "Beurer", 6) &&
		   !strncmp(model, "Gluco Memory", 12)) {
		/* The Beurer GL50 evo uses a Cygnal-manufactured CD-on-a-chip
		   that only accepts a subset of SCSI commands.  Most of the
		   not-implemented commands are fine to fail, but a few,
		   particularly around the MMC or Audio commands, will put the
		   device into an unrecoverable state, so they need to be
		   avoided at all costs.
		*/
		cd->vendor = VENDOR_CYGNAL_85ED;
		cd->cdi.mask |= (
			CDC_MULTI_SESSION |
			CDC_CLOSE_TRAY | CDC_OPEN_TRAY |
			CDC_LOCK |
			CDC_GENERIC_PACKET |
			CDC_PLAY_AUDIO
			);
	}
}

/*
#include <string.h>
#include <getopt.h>

static void getopterror(int which) {
  static char error1[]="Unknown option `-x'.\n";
  static char error2[]="Missing argument for `-x'.\n";
  if (opterr) {
    if (which) {
      error2[23]=optopt;
      write(2,error2,28);
    } else {
      error1[17]=optopt;
      write(2,error1,22);
    }
  }
}

int getopt_long(int argc, char * const argv[], const char *optstring,
		const struct option *longopts, int *longindex) {
  static int lastidx,lastofs;
  char *tmp;
  if (optind==0) { optind=1; lastidx=0; }	// whoever started setting optind to 0 should be shot 
again:
  if (*optstring == '-' && optind<argc && *argv[optind]!='-') {
    optarg=argv[optind];
    ++optind;
    return 1;
  }
  if (optind>=argc || !argv[optind] || *argv[optind]!='-' || argv[optind][1]==0)
    return -1;
  if (argv[optind][1]=='-' && argv[optind][2]==0) {
    ++optind;
    return -1;
  }
  if (argv[optind][1]=='-') {	// long option 
    char* arg=argv[optind]+2;
    char* max=strchr(arg,'=');
    const struct option* o;
    const struct option* match=0;
    if (!max) max=arg+strlen(arg);
    for (o=longopts; o->name; ++o) {
      size_t tlen=max-arg;
      if (!strncmp(o->name,arg,tlen)) {	// match 
	if (strlen(o->name)==tlen) {
	  match=o;	// perfect match, not just prefix
	  break;
	}
	if (!match)
	  match=o;
	else
	  // Another imperfect match. 
	  match=(struct option*)-1;
      }
    }
    if (match!=(struct option*)-1 && (o=match)) {
      if (longindex) *longindex=o-longopts;
      if (o->has_arg>0) {
	if (*max=='=')
	  optarg=max+1;
	else {
	  optarg=argv[optind+1];
	  if (!optarg && o->has_arg==1) {	// no argument there 
	    if (*optstring==':') return ':';
	    write(2,"argument required: `",20);
	    write(2,arg,(size_t)(max-arg));
	    write(2,"'.\n",3);
	    ++optind;
	    return '?';
	  }
	  ++optind;
	}
      }
      ++optind;
      if (o->flag)
	*(o->flag)=o->val;
      else
	return o->val;
      return 0;
    }
    if (*optstring==':') return ':';
    write(2,"invalid option `",16);
    write(2,arg,(size_t)(max-arg));
    write(2,"'.\n",3);
    ++optind;
    return '?';
  }
  if (lastidx!=optind) {
    lastidx=optind; lastofs=0;
  }
  optopt=argv[optind][lastofs+1];
  if ((tmp=strchr(optstring,optopt))) {
    if (*tmp==0) {	// apparently, we looked for \0, i.e. end of argument 
      ++optind;
      goto again;
    }
    if (tmp[1]==':') {	// argument expected 
      if (tmp[2]==':' || argv[optind][lastofs+2]) {	// "-foo", return "oo" as optarg 
	if (!*(optarg=argv[optind]+lastofs+2)) optarg=0;
	goto found;
      }
      optarg=argv[optind+1];
      if (!optarg) {	// missing argument 
	++optind;
	if (*optstring==':') return ':';
	getopterror(1);
	return ':';
      }
      ++optind;
    } else {
      ++lastofs;
      return optopt;
    }
found:
    ++optind;
    return optopt;
  } else {	// not found 
    getopterror(0);
    ++optind;
    return '?';
  }
}
*/