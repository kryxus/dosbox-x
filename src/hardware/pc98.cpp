
#include "dosbox.h"
#include "setup.h"
#include "video.h"
#include "pic.h"
#include "vga.h"
#include "programs.h"
#include "support.h"
#include "setup.h"
#include "timer.h"
#include "mem.h"
#include "util_units.h"
#include "control.h"
#include "mixer.h"

#include <string.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>

using namespace std;

extern bool gdc_5mhz_mode;

void gdc_5mhz_mode_update_vars(void);

class PC98UTIL : public Program {
public:
	void Run(void) {
        string arg;

        cmd->BeginOpt();
        while (cmd->GetOpt(/*&*/arg)) {
            if (arg == "?" || arg == "help") {
                doHelp();
                break;
            }
            else if (arg == "gdc25") {
                gdc_5mhz_mode = false;
                gdc_5mhz_mode_update_vars();
                LOG_MSG("PC-98: GDC is running at %.1fMHz.",gdc_5mhz_mode ? 5.0 : 2.5);
                WriteOut("GDC is now running at 2.5MHz\n");
            }
            else if (arg == "gdc50") {
                gdc_5mhz_mode = true;
                gdc_5mhz_mode_update_vars();
                LOG_MSG("PC-98: GDC is running at %.1fMHz.",gdc_5mhz_mode ? 5.0 : 2.5);
                WriteOut("GDC is now running at 5MHz\n");
            }
            else {
                WriteOut("Unknown switch %s",arg.c_str());
                break;
            }
        }
        cmd->EndOpt();
	}
    void doHelp(void) {
        WriteOut("PC98UTIL PC-98 emulation utility\n");
        WriteOut("  /gdc25     Set GDC to 2.5MHz\n");
        WriteOut("  /gdc50     Set GDC to 5.0MHz\n");
    }
};

void PC98UTIL_ProgramStart(Program * * make) {
	*make=new PC98UTIL;
}
