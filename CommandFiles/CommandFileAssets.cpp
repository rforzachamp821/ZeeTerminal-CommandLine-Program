void colour(std::string, std::string);


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
		colour(YLW, BLK);
		std::cout << "An error occured, and the colour has not been changed.\nPlease try again later.\n";
		break;
	}

	return;
}

// A switch-case function for the ColourForeground function.
void ColourForegroundSwitch(int* nChoice, std::string* sSettingVariableBack, std::string* sSettingVariable) {
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
		colour(YLW, BLK);
		std::cout << "An error occured, and the colour has not been changed.\nPlease try again later.\n";
		break;
	}

	return;
}