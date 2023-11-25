void colour(std::string, std::string);
void sleep(long long int);

extern ConfigFileSystem ConfigObjMain;


// A switch-case function for the ColourBackground function.
void ColourBackgroundSwitch(int* nChoice, std::string* sSettingVariableBack, std::string* sSettingVariable) {
	// Switch case for selecting colour
	switch (*nChoice) {
	case 1:
		colour(*sSettingVariable, BLK);
		*sSettingVariableBack = BLK;
		break;
	case 2:
		colour(*sSettingVariable, BLU);
		*sSettingVariableBack = BLU;
		break;
	case 3:
		colour(*sSettingVariable, GRN);
		*sSettingVariableBack = GRN;
		break;
	case 4:
		colour(*sSettingVariable, CYN);
		*sSettingVariableBack = CYN;
		break;
	case 5:
		colour(*sSettingVariable, RED);
		*sSettingVariableBack = RED;
		break;
	case 6:
		colour(*sSettingVariable, MAG);
		*sSettingVariableBack = MAG;
		break;
	case 7:
		colour(*sSettingVariable, YLW);
		*sSettingVariableBack = YLW;
		break;
	case 8:
		colour(*sSettingVariable, WHT);
		*sSettingVariableBack = WHT;
		break;
	case 9:
		colour(*sSettingVariable, GRAY);
		*sSettingVariableBack = GRAY;
		break;
	case 10:
		colour(*sSettingVariable, LBLU);
		*sSettingVariableBack = LBLU;
		break;
	case 11:
		colour(*sSettingVariable, LGRN);
		*sSettingVariableBack = LGRN;
		break;
	case 12:
		colour(*sSettingVariable, LCYN);
		*sSettingVariableBack = LCYN;
		break;
	case 13:
		colour(*sSettingVariable, LRED);
		*sSettingVariableBack = LRED;
		break;
	case 14:
		colour(*sSettingVariable, LMAG);
		*sSettingVariableBack = LMAG;
		break;
	case 15:
		colour(*sSettingVariable, LYLW);
		*sSettingVariableBack = LYLW;
		break;
	case 16:
		colour(*sSettingVariable, LWHT);
		*sSettingVariableBack = LWHT;
		break;
	default:
		VerbosityDisplay("In ColourBackgroundSwitch() - ERROR: Default switch case statement activated, so nChoice seems to be incorrect.\n");
		UserErrorDisplay("An error occured, and the colour has not been changed.\nPlease try again later.\n");
		break;
	}

	ConfigObjMain.WriteConfigFile();

	return;
}

// A switch-case function for the ColourForeground function.
void ColourForegroundSwitch(int* nChoice, std::string* sSettingVariableBack, std::string* sSettingVariable) 
{
	// Switch case for selecting colour
	switch (*nChoice) {
	case 1:
		colour(BLK, *sSettingVariableBack);
		*sSettingVariable = BLK;
		break;
	case 2:
		colour(BLU, *sSettingVariableBack);
		*sSettingVariable = BLU;
		break;
	case 3:
		colour(GRN, *sSettingVariableBack);
		*sSettingVariable = GRN;
		break;
	case 4:
		colour(CYN, *sSettingVariableBack);
		*sSettingVariable = CYN;
		break;
	case 5:
		colour(RED, *sSettingVariableBack);
		*sSettingVariable = RED;
		break;
	case 6:
		colour(MAG, *sSettingVariableBack);
		*sSettingVariable = MAG;
		break;
	case 7:
		colour(YLW, *sSettingVariableBack);
		*sSettingVariable = YLW;
		break;
	case 8:
		colour(WHT, *sSettingVariableBack);
		*sSettingVariable = WHT;
		break;
	case 9:
		colour(GRAY, *sSettingVariableBack);
		*sSettingVariable = GRAY;
		break;
	case 10:
		colour(LBLU, *sSettingVariableBack);
		*sSettingVariable = LBLU;
		break;
	case 11:
		colour(LGRN, *sSettingVariableBack);
		*sSettingVariable = LGRN;
		break;
	case 12:
		colour(LCYN, *sSettingVariableBack);
		*sSettingVariable = LCYN;
		break;
	case 13:
		colour(LRED, *sSettingVariableBack);
		*sSettingVariable = LRED;
		break;
	case 14:
		colour(LMAG, *sSettingVariableBack);
		*sSettingVariable = LMAG;
		break;
	case 15:
		colour(LYLW, *sSettingVariableBack);
		*sSettingVariable = LYLW;
		break;
	case 16:
		colour(LWHT, *sSettingVariableBack);
		*sSettingVariable = LWHT;
		break;
	default:
		VerbosityDisplay("In ColourForegroundSwitch() - ERROR: Default switch case statement activated, so nChoice seems to be incorrect.\n");
		UserErrorDisplay("An error occured, and the colour has not been changed.\nPlease try again later.\n");
		break;
	}

	ConfigObjMain.WriteConfigFile();

	return;
}

// A switch-case function that returns a colour associated with its number.
std::string NumberToColour(int nNumberChoice) {

	// Switch case based on number choice
	switch (nNumberChoice) {
	case 1:
		return BLK;
		break;
	case 2:
		return BLU;
		break;
	case 3:
		return GRN;
		break;
	case 4:
		return CYN;
		break;
	case 5:
		return RED;
		break;
	case 6:
		return MAG;
		break;
	case 7:
		return YLW;
		break;
	case 8:
		return WHT;
		break;
	case 9:
		return GRAY;
		break;
	case 10:
		return LBLU;
		break;
	case 11:
		return LGRN;
		break;
	case 12:
		return LCYN;
		break;
	case 13:
		return LRED;
		break;
	case 14:
		return LMAG;
		break;
	case 15:
		return LYLW;
		break;
	case 16:
		return LWHT;
		break;
	default:
		VerbosityDisplay("ERROR - An error occured when returning the colour string associated with its number. This is probably a bug.\n");
		break;
	}

	return "";
}

// A switch-case function for the MessageBox command (icon).
int MessageBoxIconSwitch(std::string sIconName) {
	// Make argument lowercase
	for (int i = 0; i < sIconName.length(); i++) {
		sIconName[i] = std::tolower(sIconName[i]);
	}

	if (sIconName == "error") {
		return 16;
	}
	else if (sIconName == "question") {
		return 32;
	}
	else if (sIconName == "warning") {
		return 48;
	}
	else if (sIconName == "info") {
		return 64;
	}
	else {
		VerbosityDisplay("In MessageBoxIconSwitch() - ERROR: Incorrect icon argument detected.\n");
		UserErrorDisplay("ERROR - The specified icon argument seems to be incorrect.\nPlease add one from the list of icon options.\nSee 'messagebox -h' for more info.\n");

		return 1;
	}

	return 1;
}

// A switch-case function for the MessageBox command (buttons)
int MessageBoxButtonSwitch(std::string sButtonName) {
	// Make argument lowercase
	for (int i = 0; i < sButtonName.length(); i++) {
		sButtonName[i] = std::tolower(sButtonName[i]);
	}

	if (sButtonName == "ok") {
		return 0;
	}
	else if (sButtonName == "okcancel") {
		return 1;
	}
	else if (sButtonName == "abortretryignore") {
		return 2;
	}
	else if (sButtonName == "yesnocancel") {
		return 3;
	}
	else if (sButtonName == "yesno") {
		return 4;
	}
	else if (sButtonName == "retrycancel") {
		return 5;
	}
	else if (sButtonName == "canceltrycontinue") {
		return 6;
	}
	else {
		VerbosityDisplay("In MessageBoxButtonSwitch() - ERROR: Incorrect button argument detected.\n");
		UserErrorDisplay("ERROR - Your button argument seems to be incorrect.\nPlease make sure it is from the list of button options.\nSee 'messagebox -h' for more info. Using default option...\n");

		return 0;
	}

	return 0;
}

// A switch-case function that returns the win32 equivalent of ANSI colours
std::string Win32ToAnsiColours(std::string sWin32Colour) 
{
	if (sWin32Colour == BLK_WIN32) {
		return BLK_ANSI;
	}
	else if (sWin32Colour == RED_WIN32) {
		return RED_ANSI;
	}
	else if (sWin32Colour == GRN_WIN32) {
		return GRN_ANSI;
	}
	else if (sWin32Colour == YLW_WIN32) {
		return YLW_ANSI;
	}
	else if (sWin32Colour == BLU_WIN32) {
		return BLU_ANSI;
	}
	else if (sWin32Colour == MAG_WIN32) {
		return MAG_ANSI;
	}
	else if (sWin32Colour == CYN_WIN32) {
		return CYN_ANSI;
	}
	else if (sWin32Colour == WHT_WIN32) {
		return WHT_ANSI;
	}
	else if (sWin32Colour == GRAY_WIN32) {
		return GRAY_ANSI;
	}
	else if (sWin32Colour == LRED_WIN32) {
		return LRED_ANSI;
	}
	else if (sWin32Colour == LGRN_WIN32) {
		return LGRN_ANSI;
	}
	else if (sWin32Colour == LYLW_WIN32) {
		return LYLW_ANSI;
	}
	else if (sWin32Colour == LBLU_WIN32) {
		return LBLU_ANSI;
	}
	else if (sWin32Colour == LMAG_WIN32) {
		return LMAG_ANSI;
	}
	else if (sWin32Colour == LCYN_WIN32) {
		return LCYN_ANSI;
	}
	else if (sWin32Colour == LWHT_WIN32) {
		return LWHT_ANSI;
	}
	else {
		return "";
	}
}

// A switch-case function that returns the ANSI RGB equivalent of Win32 colours
std::string AnsiToWin32Colours(std::string sAnsiColour)
{
	if (sAnsiColour == BLK_ANSI) {
		return BLK_WIN32;
	}
	else if (sAnsiColour == RED_ANSI) {
		return RED_WIN32;
	}
	else if (sAnsiColour == GRN_ANSI) {
		return GRN_WIN32;
	}
	else if (sAnsiColour == YLW_ANSI) {
		return YLW_WIN32;
	}
	else if (sAnsiColour == BLU_ANSI) {
		return BLU_WIN32;
	}
	else if (sAnsiColour == MAG_ANSI) {
		return MAG_WIN32;
	}
	else if (sAnsiColour == CYN_ANSI) {
		return CYN_WIN32;
	}
	else if (sAnsiColour == WHT_ANSI) {
		return WHT_WIN32;
	}
	else if (sAnsiColour == GRAY_ANSI) {
		return GRAY_WIN32;
	}
	else if (sAnsiColour == LRED_ANSI) {
		return LRED_WIN32;
	}
	else if (sAnsiColour == LGRN_ANSI) {
		return LGRN_WIN32;
	}
	else if (sAnsiColour == LYLW_ANSI) {
		return LYLW_WIN32;
	}
	else if (sAnsiColour == LBLU_ANSI) {
		return LBLU_WIN32;
	}
	else if (sAnsiColour == LMAG_ANSI) {
		return LMAG_WIN32;
	}
	else if (sAnsiColour == LCYN_ANSI) {
		return LCYN_WIN32;
	}
	else if (sAnsiColour == LWHT_ANSI) {
		return LWHT_WIN32;
	}
	else {
		return "";
	}
}

// Mission Impossible Theme Song in Beeps
//
void MissionImpossibleTheme() {
	MultimediaEngine meSong;

	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(932, 150);
	sleep(150);
	meSong.BeepSound(1047, 150);
	sleep(150);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(699, 150);
	sleep(150);
	meSong.BeepSound(740, 150);
	sleep(150);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(932, 150);
	sleep(150);
	meSong.BeepSound(1047, 150);
	sleep(150);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(784, 150);
	sleep(300);
	meSong.BeepSound(699, 150);
	sleep(150);
	meSong.BeepSound(740, 150);
	sleep(150);
	meSong.BeepSound(932, 150);
	meSong.BeepSound(784, 150);
	meSong.BeepSound(587, 1200);
	sleep(75);
	meSong.BeepSound(932, 150);
	meSong.BeepSound(784, 150);
	meSong.BeepSound(554, 1200);
	sleep(75);
	meSong.BeepSound(932, 150);
	meSong.BeepSound(784, 150);
	meSong.BeepSound(523, 1200);
	sleep(150);
	meSong.BeepSound(466, 150);
	meSong.BeepSound(523, 150);

	return;
}

// Happy Birthday Song in Beep Sounds
//
void HappyBirthdaySong() {
	MultimediaEngine meSong;
	
	meSong.BeepSound(1059.274, 300);
	meSong.BeepSound(1059.274, 200);
	meSong.BeepSound(1188.995, 500);
	meSong.BeepSound(1059.274, 500);
	meSong.BeepSound(1413.961, 500);
	meSong.BeepSound(1334.601, 950);

	meSong.BeepSound(1059.274, 300);
	meSong.BeepSound(1059.274, 200);
	meSong.BeepSound(1188.995, 500);
	meSong.BeepSound(1059.274, 500);
	meSong.BeepSound(1587.117, 500);
	meSong.BeepSound(1413.961, 950);

	meSong.BeepSound(1059.274, 300);
	meSong.BeepSound(1059.274, 200);
	meSong.BeepSound(2118.547, 500);
	meSong.BeepSound(1781.479, 500);
	meSong.BeepSound(1413.961, 500);
	meSong.BeepSound(1334.601, 500);
	meSong.BeepSound(1188.995, 500);
	meSong.BeepSound(1887.411, 300);
	meSong.BeepSound(1887.411, 200);
	meSong.BeepSound(1781.479, 500);
	meSong.BeepSound(1413.961, 500);
	meSong.BeepSound(1587.117, 500);
	meSong.BeepSound(1413.961, 900);

	return;
}

// Super Mario Theme Song in Beep Sounds
//
void SuperMarioTheme() {

	MultimediaEngine meSong;

	meSong.BeepSound(659, 125);
	meSong.BeepSound(659, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(167);
	meSong.BeepSound(523, 125);
	meSong.BeepSound(659, 125);
	sleep(125);
	meSong.BeepSound(784, 125);
	sleep(375);
	meSong.BeepSound(392, 125);
	sleep(375);
	meSong.BeepSound(523, 125);
	sleep(250);
	meSong.BeepSound(392, 125);
	sleep(250);
	meSong.BeepSound(330, 125);
	sleep(250);
	meSong.BeepSound(440, 125);
	sleep(125);
	meSong.BeepSound(494, 125);
	sleep(125);
	meSong.BeepSound(466, 125);
	sleep(42);
	meSong.BeepSound(440, 125);
	sleep(125);
	meSong.BeepSound(392, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(125);
	meSong.BeepSound(784, 125);
	sleep(125);
	meSong.BeepSound(880, 125);
	sleep(125);
	meSong.BeepSound(698, 125);
	meSong.BeepSound(784, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(125);
	meSong.BeepSound(523, 125);
	sleep(125);
	meSong.BeepSound(587, 125);
	meSong.BeepSound(494, 125);
	sleep(125);
	meSong.BeepSound(523, 125);
	sleep(250);
	meSong.BeepSound(392, 125);
	sleep(250);
	meSong.BeepSound(330, 125);
	sleep(250);
	meSong.BeepSound(440, 125);
	sleep(125);
	meSong.BeepSound(494, 125);
	sleep(125);
	meSong.BeepSound(466, 125);
	sleep(42);
	meSong.BeepSound(440, 125);
	sleep(125);
	meSong.BeepSound(392, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(125);
	meSong.BeepSound(784, 125);
	sleep(125);
	meSong.BeepSound(880, 125);
	sleep(125);
	meSong.BeepSound(698, 125);
	meSong.BeepSound(784, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(125);
	meSong.BeepSound(523, 125);
	sleep(125);
	meSong.BeepSound(587, 125);
	meSong.BeepSound(494, 125);
	sleep(375);
	meSong.BeepSound(784, 125);
	meSong.BeepSound(740, 125);
	meSong.BeepSound(698, 125);
	sleep(42);
	meSong.BeepSound(622, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(167);
	meSong.BeepSound(415, 125);
	meSong.BeepSound(440, 125);
	meSong.BeepSound(523, 125);
	sleep(125);
	meSong.BeepSound(440, 125);
	meSong.BeepSound(523, 125);
	meSong.BeepSound(587, 125);
	sleep(250);
	meSong.BeepSound(784, 125);
	meSong.BeepSound(740, 125);
	meSong.BeepSound(698, 125);
	sleep(42);
	meSong.BeepSound(622, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(167);
	meSong.BeepSound(698, 125);
	sleep(125);
	meSong.BeepSound(698, 125);
	meSong.BeepSound(698, 125);
	sleep(625);
	meSong.BeepSound(784, 125);
	meSong.BeepSound(740, 125);
	meSong.BeepSound(698, 125);
	sleep(42);
	meSong.BeepSound(622, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(167);
	meSong.BeepSound(415, 125);
	meSong.BeepSound(440, 125);
	meSong.BeepSound(523, 125);
	sleep(125);
	meSong.BeepSound(440, 125);
	meSong.BeepSound(523, 125);
	meSong.BeepSound(587, 125);
	sleep(250);
	meSong.BeepSound(622, 125);
	sleep(250);
	meSong.BeepSound(587, 125);
	sleep(250);
	meSong.BeepSound(523, 125);
	sleep(1125);
	meSong.BeepSound(784, 125);
	meSong.BeepSound(740, 125);
	meSong.BeepSound(698, 125);
	sleep(42);
	meSong.BeepSound(622, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(167);
	meSong.BeepSound(415, 125);
	meSong.BeepSound(440, 125);
	meSong.BeepSound(523, 125);
	sleep(125);
	meSong.BeepSound(440, 125);
	meSong.BeepSound(523, 125);
	meSong.BeepSound(587, 125);
	sleep(250);
	meSong.BeepSound(784, 125);
	meSong.BeepSound(740, 125);
	meSong.BeepSound(698, 125);
	sleep(42);
	meSong.BeepSound(622, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(167);
	meSong.BeepSound(698, 125);
	sleep(125);
	meSong.BeepSound(698, 125);
	meSong.BeepSound(698, 125);
	sleep(625);
	meSong.BeepSound(784, 125);
	meSong.BeepSound(740, 125);
	meSong.BeepSound(698, 125);
	sleep(42);
	meSong.BeepSound(622, 125);
	sleep(125);
	meSong.BeepSound(659, 125);
	sleep(167);
	meSong.BeepSound(415, 125);
	meSong.BeepSound(440, 125);
	meSong.BeepSound(523, 125);
	sleep(125);
	meSong.BeepSound(440, 125);
	meSong.BeepSound(523, 125);
	meSong.BeepSound(587, 125);
	sleep(250);
	meSong.BeepSound(622, 125);
	sleep(250);
	meSong.BeepSound(587, 125);
	sleep(250);
	meSong.BeepSound(523, 125);
	sleep(625);

	return;
}

// DunDunDun song in Beep Sounds
//
void DunDunDunSound() {
	MultimediaEngine meSong;

	meSong.BeepSound(1568, 250);
	meSong.BeepSound(1568, 250);
	meSong.BeepSound(1568, 250);
	meSong.BeepSound(1245, 1250);
	meSong.BeepSound(1397, 250);
	meSong.BeepSound(1397, 250);
	meSong.BeepSound(1397, 250);
	meSong.BeepSound(1175, 1250);

	return;
}

// Star Wars Imperial March Theme in Beep Sounds
//
void StarWarsImperialMarch() {
	MultimediaEngine meSong;

	meSong.BeepSound(440, 500);
	meSong.BeepSound(440, 500);
	meSong.BeepSound(440, 500);
	meSong.BeepSound(349, 350);
	meSong.BeepSound(523, 150);
	meSong.BeepSound(440, 500);
	meSong.BeepSound(349, 350);
	meSong.BeepSound(523, 150);
	meSong.BeepSound(440, 1000);
	meSong.BeepSound(659, 500);
	meSong.BeepSound(659, 500);
	meSong.BeepSound(659, 500);
	meSong.BeepSound(698, 350);
	meSong.BeepSound(523, 150);
	meSong.BeepSound(415, 500);
	meSong.BeepSound(349, 350);
	meSong.BeepSound(523, 150);
	meSong.BeepSound(440, 1000);

	return;
}

// HackerTyper - Traditional hacker-typer using a snippet of the linux kernel source code
// Arguments: nSpeed - The speed of the character output in characters.
// Return Values: None
// 
void HackerTyper(uint64_t nSpeed = 3) {
	std::string sHackerText = "struct group_info init_groups = { .usage = ATOMIC_INIT(2) };\n\nstruct group_info *groups_alloc(int gidsetsize){\n\n   struct group_info *group_info;\n\n       int nblocks;\n\n        int i;\n\n\n\n  nblocks = (gidsetsize + NGROUPS_PER_BLOCK - 1) / NGROUPS_PER_BLOCK;\n\n /* Make sure we always allocate at least one indirect block pointer */\n\n      nblocks = nblocks ? : 1;\n\n    group_info = kmalloc(sizeof(*group_info) + nblocks*sizeof(gid_t *), GFP_USER);\n\n      if (!group_info)\n\n            return NULL;\n\n        group_info->ngroups = gidsetsize;\n\n   group_info->nblocks = nblocks;\n\n      atomic_set(&group_info->usage, 1);\n\n\n\n      if (gidsetsize <= NGROUPS_SMALL)\n\n            group_info->blocks[0] = group_info->small_block;\n\n    else {\n\n              for (i = 0; i < nblocks; i++) {\n\n                    gid_t *b;\n\n                    b = (void *)__get_free_page(GFP_USER);\n\n                      if (!b)\n\n            goto out_undo_partial_alloc;\n\n                 group_info->blocks[i] = b;\n\n          }\n\n   }\n\n   return group_info;\n\n\n\nout_undo_partial_alloc:\n\n   while (--i >= 0) {\n\n          free_page((unsigned long)group_info->blocks[i]);\n\n    }\n\n   kfree(group_info);\n\n  return NULL;\n\n}\n\n\n\nEXPORT_SYMBOL(groups_alloc);\n\n\n\nvoid groups_free(struct group_info *group_info)\n\n{\n\n   if (group_info->blocks[0] != group_info->small_block) {\n\n             int i;\n\n              for (i = 0; i < group_info->nblocks; i++)\n\n                   free_page((unsigned long)group_info->blocks[i]);\n\n    }\n\n   kfree(group_info);\n\n}\n\n\n\nEXPORT_SYMBOL(groups_free);\n\n\n\n/* export the group_info to a user-space array */\n\nstatic int groups_to_user(gid_t __user *grouplist,\n\n                     const struct group_info *group_info)\n\n{\n\n int i;\n\n      unsigned int count = group_info->ngroups;\n\n\n\n       for (i = 0; i < group_info->nblocks; i++) {\n\n         unsigned int cp_count = min(NGROUPS_PER_BLOCK, count);\n\n              unsigned int len = cp_count * sizeof(*grouplist);\n\n\n\n               if (copy_to_user(grouplist, group_info->blocks[i], len))\n\n   return -EFAULT;\n\n\n\n          grouplist += NGROUPS_PER_BLOCK;\n\n             count -= cp_count;\n\n  }\n\n   return 0;\n\n}\n\n\n\n/* fill a group_info from a user-space array - it must be allocated already */\n\nstatic int groups_from_user(struct group_info *group_info,\n\n    gid_t __user *grouplist)\n\n{\n\n     int i;\n\n      unsigned int count = group_info->ngroups;\n\n\n\n       for (i = 0; i < group_info->nblocks; i++) {\n\n         unsigned int cp_count = min(NGROUPS_PER_BLOCK, count);\n\n              unsigned int len = cp_count * sizeof(*grouplist);\n\n\n\n               if (copy_from_user(group_info->blocks[i], grouplist, len))\n\n                  return -EFAULT;\n\n\n\n         grouplist += NGROUPS_PER_BLOCK;\n\n             count -= cp_count;\n\n  }\n\n   return 0;\n\n}\n\n\n\n/* a simple Shell sort */\n\nstatic void groups_sort(struct group_info *group_info)\n\n{\n\n      int base, max, stride;\n\n      int gidsetsize = group_info->ngroups;\n\n\n\n   for (stride = 1; stride < gidsetsize; stride = 3 * stride + 1)\n\n              ; /* nothing */\n\n     stride /= 3;\n\n\n\n    while (stride) {\n\n            max = gidsetsize - stride;\n\n          for (base = 0; base < max; base++) {\n\n                        int left = base;\n\n                    int right = left + stride;\n\n gid_t tmp = GROUP_AT(group_info, right);\n\n\n\n                 while (left >= 0 && GROUP_AT(group_info, left) > tmp) {\n\n                             GROUP_AT(group_info, right) =\n\n                                   GROUP_AT(group_info, left);\n\n                             right = left;\n\n                               left -= stride;\n\n            }\n\n                    GROUP_AT(group_info, right) = tmp;\n\n          }\n\n           stride /= 3;\n\n        }\n\n}\n\n\n\n/* a simple bsearch */\n\nint groups_search(const struct group_info *group_info, gid_t grp)\n\n{\n\n      unsigned int left, right;\n\n\n\n       if (!group_info)\n\n            return 0;\n\n\n\n       left = 0;\n\n   right = group_info->ngroups;\n\n        while (left < right) {\n\n              unsigned int mid = left + (right - left)/2;\n\n        if (grp > GROUP_AT(group_info, mid))\n\n                 left = mid + 1;\n\n             else if (grp < GROUP_AT(group_info, mid))\n\n                   right = mid;\n\n                else\n\n                        return 1;\n\n   }\n\n  return 0;\n\n}\n\n\n\n";
	char cKey = 0; // Key pressed (for exit functions and stuff)

	// Change colour to RGB Green
	colour(LGRN, ConfigObjMain.sColourGlobalBack);

	// Output based on nSpeed speed, and exit on ESC keypress
	std::cout << " --> ";
	while (cKey != 27)
	{
		for (uint64_t i = 0; i < sHackerText.length(); i += nSpeed)
		{
			// Get key
			cKey = _getch();
			// Exit on ESC keypress (27 is ASCII Code)
			if (cKey == 27) break;

			// Near the end of the string - Output up to end of sHackerText
			if (sHackerText.length() - 1 < (i + nSpeed))
			{
				for (; i < sHackerText.length(); i++)
				{
					std::cout << sHackerText[i];
				}

				break;
			}

			// In the middle of string - Output normally
			else
			{
				uint64_t nCapChanger = 0; // to change limit of j
				for (uint64_t j = 0; j < nSpeed + nCapChanger; j++)
				{
					std::cout << sHackerText[i + j];

					// Ignore space counting by increasing cap
					if (sHackerText[i + j] == ' ') nCapChanger++;
				}

				// Increment i by the cap to get it up to speed
				i += nCapChanger;
			}
		}
	}

	// Switch colours to default
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	std::cout << '\n';
	Exiting();
	return;
}

// HackerTyperFile - A hacker typer, but you can use your own file for the text.
// Arguments: sFilePath - The file path for the custom file to be used.
//            nSpeed - The speed of the character output in characters.
// Return Values: TRUE or 1 for success, FALSE or 0 for fail.
// 
bool HackerTyperFile(std::string sFilePath, uint64_t nSpeed = 3) {
	std::string sFinalFilePath = "";
	char cKey = 0;

	// Check for speechmarks in case of copy from file explorer
	if (sFilePath[0] == '"' && sFilePath[sFilePath.length() - 1] == '"') {
		sFinalFilePath = sFilePath.substr(1, (sFilePath.length() - 2));
	}
	else sFinalFilePath = sFilePath;

	// Check if the file actually exists
	std::ifstream FilePathTest(sFinalFilePath);
	if (FilePathTest.fail()) {
		VerbosityDisplay("ERROR: In HackerTyperFile() - Test file stream failed to open file path. Incorrect filepath detected.\n");
		UserErrorDisplay("ERROR - File does not exist. Please ensure the filepath that has been used exists, and try again later.\n");
		FilePathTest.close();
		return false;
	}
	else FilePathTest.close();

	// Copy file into string
	std::ifstream FilePathIn(sFilePath);
	std::string sFileContents = "";
	std::string sBuffer = "";

	while (!FilePathIn.eof())
	{
		std::getline(FilePathIn, sBuffer, '\n');
		sBuffer += "\n"; // USE \\n for copying new text into string manually
		sFileContents += sBuffer;
		sBuffer = "";
	}

	// Change colour to RGB Green
	colour(LGRN, ConfigObjMain.sColourGlobalBack);

	// Output based on nSpeed speed, and exit on ESC keypress
	std::cout << " --> ";
	while (cKey != 27)
	{
		for (uint64_t i = 0; i < sFileContents.length(); i += nSpeed)
		{
			// Get key
			cKey = _getch();
			// Exit on ESC keypress (27 is ASCII Code)
			if (cKey == 27) break;

			// Near the end of the string - Output up to end of sFileContents
			if (sFileContents.length() - 1 < (i + nSpeed))
			{
				for (; i < sFileContents.length(); i++)
				{
					std::cout << sFileContents[i];
				}

				break;
			}

			// In the middle of string - Output normally
			else
			{
				uint64_t nCapChanger = 0; // to change limit of j
				for (uint64_t j = 0; j < nSpeed + nCapChanger; j++)
				{
					std::cout << sFileContents[i + j];

					// Ignore space counting by increasing cap
					if (sFileContents[i + j] == ' ') nCapChanger++;
				}

				// Increment i by the cap to get it up to speed
				i += nCapChanger;
			}
		}
	}

	// Switch colours to default
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	std::cout << '\n';
	Exiting();

	return true;
}

// ResetExpl - Resets explorer.exe on the system running ZeeTerminal.
// Arguments: None
// Return values: TRUE or 1 for success, FALSE or 0 for fail.
//
bool ResetExpl() {
	
	// Kill explorer.exe
	system("taskkill /f /im explorer.exe");

	// Start explorer.exe using ShellExecuteA
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	if (FAILED(hr)) {
		VerbosityDisplay("In ResetExpl() - ERROR: Failed to initialise the COM Library.\n");
		UserErrorDisplay("ERROR - Failed to load libraries that are required for operation. Please try again later.\n");

		return false;
	}

	ShellExecuteA(NULL, "open", "C:\\Windows\\explorer.exe", NULL, "C:\\Windows\\", NULL);

	return true;
}


/* MessageBox Codes */
//////////////////////
/* Message box codes are the following for icons:
   [16] Error
   [32] Question Mark
   [48] Exclamation Mark
   [64] Information 'I'
*/
/* Message box codes are the following for buttons:
   [0] OK
   [1] OK + Cancel
   [2] Abort + Retry + Ignore
   [3] Yes + No + Cancel
   [4] Yes + No
   [5] Retry + Cancel
   [6] Cancel + Try Again + Continue
 */