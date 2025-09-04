//
// CarDodgeMain.cpp - Houses the CarDodgeMain class functions.
//
#include "CarDodgeMain.h"
#include "../../../../Core/ZeeTerminalCore.h"
#include "../../../../Core/ZTFormattingDefinitions.h"
#include "../../../../Engine/OptionSelectEngine/OptionSelectEngine.h"
#include "../CarDodgeCore/CarDodgeCore.h"
#include "../CarInfo/CarInfo.h"
#include "../../../../GameFiles/GameHighScoresSystem/GameHighScoresSystem.h"
#include <conio.h>

extern short int nSessionConsoleHeight;
extern CarInfo UserCar;
extern CarInfo EnemyCars[128];
extern const int nEnemyCarArraySize;

bool VerifyIfGameIsRunnable(bool, bool);

// UpdatePanelInfo
void CarDodgeMain::UpdatePanelInfo() {
	// Set to colour of panel before anything
	colour(sBorderColourFore, sBorderColourBack);

	// Render unchanging title/controls if not rendered already
	if (!bPanelAlreadyUpdated) {
		// Render unchanging title if not rendered already
		SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 2);
		std::cout << "*************";
		SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 3);
		std::cout << "| Car Dodge |";
		SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 4);
		std::cout << "*************";

		// Render unchanging controls if not rendered already
		SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 13);
		std::cout << "|    __Controls__   |";
		SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 14);
		std::cout << "| Left:             |";
		SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 15);
		std::cout << "| Left Arrow/A Key  |";
		SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 16);
		std::cout << "| Right:            |";
		SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 17);
		std::cout << "| Right Arrow/D Key |";

		bPanelAlreadyUpdated = true;
	}

	SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 6);
	std::cout << "_______________";
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 7);
	std::cout << "Points: " << nSessionPoints;
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 8);
	std::cout.write(std::string(nRightBorderWidth - 3, ' ').data(), nRightBorderWidth - 3);
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 8);
	std::cout << "Time: " << nSessionTime.count() << " sec";
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 9);
	std::cout << "Level: " << (nSessionLevel == 12 ? "OMEGA" : std::to_string(nSessionLevel));
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 10);
	std::cout << "Interval Period: " << nSessionEnemyCarInterval.count() * (nSessionPowerUp == 1 ? 2 : 1) << (nSessionEnemyCarInterval.count() * (nSessionPowerUp == 1 ? 2 : 1) < 100 ? "ms " : "ms"); // Display milliseconds with a space when less than 100ms (3 digits) interval period to prevent overflow to next line
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 3, 11);
	std::cout << "_______________";

	// Render power-up box
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 25);
	std::cout << "|___Current Power-Up__|";
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 26);
	std::cout << "| ";
	// Write the right current power-up text to display based on nSessionPowerUp variable
	if (nSessionPowerUp == 0 && bExtraLife == true) {
		colour(BLK, LCYN);
		std::cout << "ExtraLife Activated";
	}
	else if (nSessionPowerUp == 0) std::cout << "    No Power-Up    ";
	else if (nSessionPowerUp == 1) {
		colour(BLK, LYLW);
		std::cout << "  10sec 2x Slowdown";
	}
	else if (nSessionPowerUp == 3) {
		colour(LWHT, GRN);
		std::cout << "10sec Invincibility";
	}
	else if (nSessionPowerUp == 4) {
		colour(WHT, RED);
		std::cout << " 10sec Double Score";
	}
	else if (nSessionPowerUp == 5) {
		colour(WHT, MAG);
		std::cout << "10s 3xPowerUpChance";
	}
	colour(GetLevelBorderColourFore(), GetLevelBorderColourBack());
	std::cout << " |";
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 27);
	std::cout << "|                     |";
	SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 28);
	std::cout << "| Extra Life: " << (bExtraLife ? "Yes     |" : "No      |");

	// Reset to global colours
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	return;
}

// DisplayUserLossScreen
bool CarDodgeMain::DisplayUserLossScreen() {
	cls();
	RenderBorders(sBorderColourFore, sBorderColourBack);

	// Draw borders around loss screen with fill
	colour(YLW, RED);
	SetCursorPosition(nLeftBorderWidth, 3);
	std::cout << std::string(nGameplayScreenWidth, '#');
	for (int i = 4; i < 12; i++) {
		SetCursorPosition(nLeftBorderWidth, i);
		std::cout << std::string(nGameplayScreenWidth, ' ');
	}
	SetCursorPosition(nLeftBorderWidth, 12);
	std::cout << std::string(nGameplayScreenWidth, '#');

	// Title
	SetCursorPosition(nLeftBorderWidth, 5);
	colour(WHT, RED);
	std::cout << ULINE_STR << CentreTextCarDodge("You crashed!") << std::string((nGameplayScreenWidth - 12) / 2, ' ') << NOULINE_STR;

	//                           //
	// Display other stats \/ \/ //
	//                           //

	SetCursorPosition(nLeftBorderWidth, 7);
	std::cout << CentreTextCarDodge("Elapsed Time: ", 22 + std::to_string(nSessionTime.count()).length());
	colour(BLU, RED);
	std::cout << std::to_string(nSessionTime.count()) << " seconds";
	colour(WHT, RED);

	SetCursorPosition(nLeftBorderWidth, 8);
	std::cout << CentreTextCarDodge("Final Score: ", 13 + std::to_string(nSessionPoints).length() + std::string(nSessionPoints > GetCurrentHighScore() ? " (-- NEW HIGH SCORE --)" : "").length());
	colour(BLU, RED);
	std::cout << std::to_string(nSessionPoints);
	RandomColourOutput(std::string(nSessionPoints > GetCurrentHighScore() ? " (-- NEW HIGH SCORE --)" : ""), RED);
	colour(WHT, RED);

	SetCursorPosition(nLeftBorderWidth, 9);
	std::cout << CentreTextCarDodge("Final Level: ", 13 + std::to_string(nSessionLevel).length() + std::string(nSessionLevel == 12 ? " (OMEGA Level)" : "").length());
	colour(BLU, RED);
	std::cout << std::to_string(nSessionLevel) + std::string(nSessionLevel == 12 ? " (OMEGA Level)" : "");
	colour(WHT, RED);

	SetCursorPosition(nLeftBorderWidth, 10);
	std::cout << CentreTextCarDodge("Final Interval Period: ", 25 + std::to_string(nSessionEnemyCarInterval.count()).length());
	colour(BLU, RED);
	std::cout << std::to_string(nSessionEnemyCarInterval.count()) + "ms";
	colour(WHT, RED);

	// Restart on ENTER, exit on ESC, don't do anything on any other input
	SetCursorPosition(nLeftBorderWidth, 14);
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << " Press ENTER to try again, or press ESC to exit to main menu...\n";

	// Set high score and update high score file immediately
	SetHighScore(nSessionPoints);
	GameHighScoresSystem::SetCarDodgeHighScore(nCurrentPointsHighScore);
	GameHighScoresSystem::UpdateHighScoreFile();

	while (true) {
		char cInput = _getch();
		if (cInput == 27) return false; // Exit
		else if (cInput == 13) return true; // Restart
	}

	return false;
}

// ResetGame
void CarDodgeMain::ResetGame() {
	// Save car design to reset it later
	std::array<std::array<char, 4>, 4> UserCarStyle = UserCar.CarStyle;

	// Reset everything
	for (int i = 0; i < nEnemyCarArraySize; i++) {
		ResetCarInfoObject(&EnemyCars[i]);
		EnemyCars[i].CarStyle = CarStyles::EnemyCar;
	}
	nSessionPoints = 0;
	nSessionTime = std::chrono::milliseconds::zero();
	ResetCarInfoObject(&UserCar);
	UserCar.CarStyle = UserCarStyle;
	bPanelAlreadyUpdated = false;
	nSessionPowerUp = 0;
	nChanceForPowerUpCarMultiplier = 1;
	bExtraLife = false;

	return;
}

// GetSessionLevel
uint64_t CarDodgeMain::GetSessionLevel()
{
	// Set of if statements to calculate session level based on points range
	if (nSessionPoints >= 0 && nSessionPoints < 40) { // range of 40
		return 1;
	}
	else if (nSessionPoints >= 40 && nSessionPoints < 85) { // range of 45
		return 2;
	}
	else if (nSessionPoints >= 85 && nSessionPoints < 135) { // range of 50
		return 3;
	}
	else if (nSessionPoints >= 135 && nSessionPoints < 190) { // range of 55
		return 4;
	}
	else if (nSessionPoints >= 190 && nSessionPoints < 250) { // range of 60
		return 5;
	}
	else if (nSessionPoints >= 250 && nSessionPoints < 315) { // range of 65
		return 6;
	}
	else if (nSessionPoints >= 315 && nSessionPoints < 385) { // range of 70
		return 7;
	}
	else if (nSessionPoints >= 385 && nSessionPoints < 460) { // range of 75
		return 8;
	}
	else if (nSessionPoints >= 460 && nSessionPoints < 540) { // range of 80
		return 9;
	}
	else if (nSessionPoints >= 540 && nSessionPoints < 625) { // range of 85
		return 10;
	}
	else if (nSessionPoints >= 625 && nSessionPoints < 725) { // range of 100
		return 11;
	}
	else if (nSessionPoints >= 725) {
		return 12;
	}

	//for (uint64_t nLowerBound = 0, nUpperBound = 20, nMultiplier = 4;; nLowerBound += nLowerBound + (nMultiplier * 5), nUpperBound += nUpperBound + (nMultiplier * 5)) {
	//	if (nSessionPoints >= nLowerBound && nSessionPoints < nUpperBound) {
	//		return nMultiplier - 3;
	//	}
	//}

	// If error occurs, return current nSessionLevel
	return nSessionLevel;
}

// GetSessionEnemyCarInterval
std::chrono::milliseconds CarDodgeMain::GetSessionLevelEnemyCarInterval()
{
	// Use a switch-case for increased performance
	switch (nSessionLevel) {
	case 1:
		return std::chrono::milliseconds(60);
		break;
	case 2:
		return std::chrono::milliseconds(55);
		break;
	case 3:
		return std::chrono::milliseconds(50);
		break;
	case 4:
		return std::chrono::milliseconds(45);
		break;
	case 5:
		return std::chrono::milliseconds(40);
		break;
	case 6:
		return std::chrono::milliseconds(35);
		break;
	case 7:
		return std::chrono::milliseconds(30);
		break;
	case 8:
		return std::chrono::milliseconds(25);
		break;
	case 9:
		return std::chrono::milliseconds(20);
		break;
	case 10:
		return std::chrono::milliseconds(15);
		break;
	case 11:
		return std::chrono::milliseconds(10);
		break;
	case 12:
		return std::chrono::milliseconds(10);
		break;
	default:
		return std::chrono::milliseconds(60);
	}
}

// GetLevelBorderColourFore
std::string CarDodgeMain::GetLevelBorderColourFore() {
	// Use a switch-case statement for increased performance
	switch (nSessionLevel) {
	case 1:
		return LWHT;
	case 2:
		return LWHT;
	case 3:
		return LWHT;
	case 4:
		return LWHT;
	case 5:
		return LWHT;
	case 6:
		return LWHT;
	case 7:
		return LWHT;
	case 8:
		return BLK;
	case 9:
		return BLK;
	case 10:
		return BLK;
	case 11:
		return BLK;
	case 12:
		return BLK;
	default:
		return LWHT;
	}
}

// GetLevelBorderColourBack
std::string CarDodgeMain::GetLevelBorderColourBack() {
	// Use a switch-case statement for increased performance
	switch (nSessionLevel) {
	case 1:
		return BLU;
	case 2:
		return GRN;
	case 3:
		return YLW;
	case 4:
		return RED;
	case 5:
		return MAG;
	case 6:
		return CYN;
	case 7:
		return GRAY;
	case 8:
		return LBLU;
	case 9:
		return LGRN;
	case 10:
		return LYLW;
	case 11:
		return LRED;
	case 12:
		return LCYN;
	default:
		return BLU;
	}
}

// CarDodgeMainGame
void CarDodgeMain::CarDodgeMainGame()
{
	short int nReiterationCount = 0; // number of reiterations in game loop
	auto TimeStartPoint = std::chrono::steady_clock::now(); // For time start point for session time
	auto TimeEndPoint = std::chrono::steady_clock::now(); // For time end point for session time AND for measuring enemy car interval time
	std::chrono::steady_clock::time_point PowerUpTimeStartPoint = std::chrono::steady_clock::now(); // start point for a running powerup
	std::chrono::steady_clock::time_point PowerUpTimeEndPoint = std::chrono::steady_clock::now(); // end point for a running powerup

	bool bRestartGame = false; // Flag for restarting game (usually on game loss)

	// Ensure that all cursor and colour settings are saved before game initialisation
	const bool bShowCursorPrevious = DisableCursorVisibility();	// Set cursor attributes and hide cursor to prevent flickering
	const std::string sColourGlobalPrevFore = ConfigObjMain.sColourGlobal;
	const std::string sColourGlobalPrevBack = ConfigObjMain.sColourGlobalBack;

	// Set global colours to game colours
	ConfigObjMain.sColourGlobal = ConfigObjMain.sCarDodgeGameplayColourFore;
	ConfigObjMain.sColourGlobalBack = ConfigObjMain.sCarDodgeGameplayColourBack;

	// Game restart loop
	do
	{
		// Ensure restart flag is disabled to not cause issues
		bRestartGame = false; // in case user accidentally restarted game and wants to exit now

		// Secondly, clear screen, render borders with default starting colours (that's why there are no colour parameters) (game initialisation)
		RenderBorders();

		// Verify if game is runnable in current terminal state
		if (!VerifyIfGameIsRunnable(true, true)) {
			std::cout << "Take your time to resize the game window. This message will go when the game window is properly sized.\nPress any key to exit to main menu.\n";

			// Loop checking
			bool bBreakOutOfGameLoop = false;
			while (true) {
				// Check if user inputted anything
				if (_kbhit()) {
					_getch();
					bBreakOutOfGameLoop = true;
					break;
				}

				// Check window size repeatedly
				if (VerifyIfGameIsRunnable(true, false)) {
					// Exit loop - the window has been resized.
					break;
				}

				sleep(1);
			}

			// Exit game if key was pressed
			if (bBreakOutOfGameLoop) {
				goto GameEnd; // Exit game
			}

			// Re-render borders
			RenderBorders();
		}

		// Render user car, set user car start position
		UserCar.bottomLeft = { 43, nSessionConsoleHeight };
		UserCar.bottomRight = { 46, nSessionConsoleHeight };
		RenderCar(UserCar);

		// Set up enemy car intervals, session levels
		nSessionLevel = GetSessionLevel();
		nSessionEnemyCarInterval = GetSessionLevelEnemyCarInterval(); // must be done in this order, as GetSessionlevelEnemyCarInterval depends on GetSessionLevel to work properly

		// Start a countdown timer on centre-top of screen
		SetCursorPosition(23, 5);
		colour(BLK, LGRN);
		std::cout << "Press ENTER to begin (ESC to return to menu)... ";

		// Recieve key from user
		while (true) {
			char cKey = _getch();
			if (cKey == 27) {
				goto GameEnd; // exit game
			}
			// start game on enter
			else if (cKey == 13) {
				break;
			}
		}

		// Countdown
		for (int8_t i = 3; i > 0; i--) {
			std::cout << std::to_string(i) << " ";
			sleep(1000);
		}

		// Clear countdown text
		SetCursorPosition(23, 5);
		colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
		std::cout << std::string(54, ' ');
		ClearKeyboardBuffer();

		// Set start time point, as game is about to start
		TimeStartPoint = std::chrono::steady_clock::now();

		//
		// MAIN GAME LOOP
		//
		while (true)
		{
			// Start time point for current loop iteration (for measuring execution time for calculating enemy car production interval)
			auto LoopTimeStartPoint = std::chrono::steady_clock::now();

			// Verify if game is runnable in current terminal state
			if (!VerifyIfGameIsRunnable(true, true)) {
				std::cout << "Take your time to resize the game window. The game will resume automatically with a countdown.\nPress any key to exit to main menu.\n";

				// Loop checking
				bool bBreakOutOfGameLoop = false;
				while (true) {
					// Check if user inputted anything
					if (_kbhit()) {
						_getch();
						bBreakOutOfGameLoop = true;
						break;
					}

					// Check window size repeatedly
					if (VerifyIfGameIsRunnable(true, false)) {
						// Exit loop - the window has been resized.
						break;
					}

					sleep(1);
				}

				// Exit game loop if user presses key
				if (bBreakOutOfGameLoop == true) {
					break;
				}

				// Render new borders, as shrinking the window size will make the game graphics look messed up
				RenderBorders(GetLevelBorderColourFore(), GetLevelBorderColourBack());

				// Re-render car, as screen would have been cleared in CarDodgeCore::RenderBorders()
				RenderCar(UserCar);

				// To ensure that all panel info is properly updated, set so that panel info is updated as first-time
				bPanelAlreadyUpdated = false;

				// Countdown
				colour(BLK, LGRN);
				SetCursorPosition(30, 5);
				for (int i = 3; i > 0; i--) {
					std::cout << i << ' ';
					sleep(1000);
				}
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// Clear countdown
				SetCursorPosition(30, 5);
				std::cout << "      ";
			}

			// Get input from user if user presses key
			short int cFirstValue = ' ', cSecondValue = ' ';
			if (_kbhit()) {
				cFirstValue = _getch_nolock(); // Get input

				// 224 indicates a special character
				if (cFirstValue == 224) {
					// The value being places in cSecondValue means that it's a special character. This prevents any conflicts with other characters.
					cSecondValue = _getch_nolock();
				}
			}

			// Move left
			if (cFirstValue == 'a' || cSecondValue == 75) {
				MoveUserCarLeft(); // Move car left on 'a' OR left arrow press
			}

			// Move right
			else if (cFirstValue == 'd' || cSecondValue == 77) {
				MoveUserCarRight(); // Move car right on 'd' OR right arrow press
			}
			else if (cFirstValue == 27) {
				auto TimePointStartOfPause = std::chrono::steady_clock::now(); // Initialise start time point of pause menu.

				// Display menu text informing user that the game is paused
				colour(BLK, LYLW);
				SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 19);
				std::cout << "You are PAUSED.";
				SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 21);
				std::cout << "Press ENTER to resume.";
				SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 22);
				std::cout << "Press ESC to exit.";
				colour(sBorderColourFore, sBorderColourBack);

				bool bExitGame = false; // Exit game flag

				while (true) {
					char cInput = _getch(); // Get input

					// Break on another ESC
					if (cInput == 27) {
						bExitGame = true; // exit game flag
						break;
					}
					else if (cInput == 13) {
						break; // break as exit game flag is defaulted to false
					}
				}

				// Exit when exit game flag set to true
				if (bExitGame) break;

				// Clear menu text
				SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 19);
				std::cout << "               ";
				SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 21);
				std::cout << "                      ";
				SetCursorPosition(nScreenWidth - nRightBorderWidth + 2, 22);
				std::cout << "                  ";
				colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

				// Get current end of pause time, and increment game time start point by the amount of time spent in the pause menu.
				// This is done so the calculated amount of time in the game is correct to how long the user has actually been playing.
				auto TimePointEndOfPause = std::chrono::steady_clock::now();
				TimeStartPoint += (TimePointEndOfPause - TimePointStartOfPause);
			}

			// Check if user car collided with enemy car; if so, exit
			int nEnemyCarCollisionIndexVal = 0;
			if (CheckForCarCollision(&nEnemyCarCollisionIndexVal)) 
			{
				// Check if the car that user crashed into was a power-up car
				if (EnemyCars[nEnemyCarCollisionIndexVal].bIsPowerUpCar == true) {
					// Delete the power-up car and re-render the user car to prevent the user car from looking disintegrated
					DeleteEnemyCarAndResetSafely(nEnemyCarCollisionIndexVal);
					RenderCar(UserCar);

					// Generate random number, randomly pick a power-up
					std::random_device rdRandNumGen;
					std::uniform_int_distribution<short int> DistPowerUpGen(1, 5);
					nSessionPowerUp = DistPowerUpGen(rdRandNumGen); // Directly assign power-up now, as it should be within acceptable range.
					nChanceForPowerUpCarMultiplier = 1; // Reset power-up car chance multiplier

					// Check if nSessionPowerUp is 2; if so, set it to 0 and assign bExtraLife to true
					if (nSessionPowerUp == 2) {
						nSessionPowerUp = 0;
						bExtraLife = true;
					}
					else {
						// Else start timer for power-ups (all the other power-ups are all the same time, so this should work)
						PowerUpTimeStartPoint = std::chrono::steady_clock::now();
					}

					// Set multiplier to 3 when associated power-up is enabled
					if (nSessionPowerUp == 5) {
						nChanceForPowerUpCarMultiplier = 3;
					}
				}

				else {
					// Extra life
					if (bExtraLife == true || nSessionPowerUp == 3) {
						// Delete the power-up car and re-render the user car to prevent the user car from looking disintegrated
						DeleteEnemyCarAndResetSafely(nEnemyCarCollisionIndexVal);
						RenderCar(UserCar);

						// Do some specific things when extra life has been granted
						if (bExtraLife == true && nSessionPowerUp != 3) {
							bExtraLife = false; // No more extra life; reset associated variable

							// Reset power-ups as extra life has been granted
							nSessionPowerUp = 0;
							nChanceForPowerUpCarMultiplier = 1;
						}
					}
					else {
						bRestartGame = DisplayUserLossScreen(); // User lost
						
						// Exit game loop
						break;
					}
				}
			}

			// Render a new enemy car if there is one less than car's worth of space between another enemy car (one less because of shorter hitbox size)
			if (nReiterationCount >= 7) {
				RenderNewEnemyCar();
				nReiterationCount = 0;
			}

			// Check if an enemy car is on the lower border of the screen - if so, one enemy car has died, therefore increase points by 1.
			if (DeleteEnemyCarOnLowerBorderHit()) {
				nSessionPoints++;
				// Double the amount of session points if the associated power-up is enabled
				if (nSessionPowerUp == 4) nSessionPoints++;

				// After session points increase, check if player level should be increased and if the enemy car interval should change (this was implemented like this as an optimisation)
				uint64_t nSessionLevelPrev = nSessionLevel;
				nSessionLevel = GetSessionLevel();
				nSessionEnemyCarInterval = GetSessionLevelEnemyCarInterval();

				// Change border theme/colour when session level changed
				if (nSessionLevelPrev != nSessionLevel) {
					// Render new borders
					RenderBorders(GetLevelBorderColourFore(), GetLevelBorderColourBack());

					// Re-render car, as screen would have been cleared in CarDodgeCore::RenderBorders()
					RenderCar(UserCar);

					// To ensure that all panel info is properly updated, set so that panel info is updated as first-time
					bPanelAlreadyUpdated = false;
				}
			}

			// Move all enemy cars by 1 forward.
			MoveAllEnemyCars();

			// Get current user playing time
			TimeEndPoint = std::chrono::steady_clock::now();
			nSessionTime = TimeEndPoint - TimeStartPoint;

			// Update right border panel info (with points, time, etc)
			UpdatePanelInfo();

			// Increase reiteration count to indicate when the next enemy car should be created
			nReiterationCount++;

			// Check if power-up time has reached 15 seconds; if so, set the nSessionPowerUp variable to 0
			if (nSessionPowerUp > 0) {
				PowerUpTimeEndPoint = std::chrono::steady_clock::now();
				// Get power-up time
				std::chrono::milliseconds nPowerUpTime = std::chrono::duration_cast<std::chrono::milliseconds>(PowerUpTimeEndPoint - PowerUpTimeStartPoint);

				// Reset nSessionPowerUp variable if power up time complete
				if (nPowerUpTime >= std::chrono::milliseconds(10000)) {
					nSessionPowerUp = 0;
					nChanceForPowerUpCarMultiplier = 1; // Reset power-up car chance multiplier variable
				}
			}

			// Get current time again, for measuring how much time is needed to wait for next loop
			std::chrono::duration<uint64_t, std::milli> ExecTime{};
			TimeEndPoint = std::chrono::steady_clock::now();
			// Work out execution time of this loop
			std::chrono::milliseconds nExecTime = std::chrono::duration_cast<std::chrono::milliseconds>(TimeEndPoint - LoopTimeStartPoint);

			// Check if execution time is less than required interval speed. If so, sleep until interval speed is reached, else continue
			if (nExecTime < nSessionEnemyCarInterval * (nSessionPowerUp == 1 ? 2 : 1))
			{
				// The following code is equivalent to:
				// 
				// Sleep(nSessionEnemyCarInterval - ExecTime.count());
				// 
				// without making the thread sleep.
				//
				for (;;) {
					// Wait until execution time of current game loop iteration is the enemy car interval time.
					// This is to prevent the user gaining a reaction time advantage and game scores being invalid.
					const auto TimeNow = std::chrono::steady_clock::now();
					if (TimeEndPoint + (nSessionEnemyCarInterval * (nSessionPowerUp == 1 ? 2 : 1) - ExecTime) <= TimeNow) {
						break;
					}
				}
			}

		} // game loop end brace

	GameEnd: // goto statement for exiting game

		// Set the high score and update high score file with it
		// 
		// SetHighScore sets the high score automatically - we don't need logic as to if the current score is higher than the high score, as that's already in there
		SetHighScore(nSessionPoints);
		// Update the high score in the High Score file
		ConfigObjMain.bShowCursor = bShowCursorPrevious;
		GameHighScoresSystem::SetCarDodgeHighScore(nCurrentPointsHighScore);
		GameHighScoresSystem::UpdateHighScoreFile();
		DisableCursorVisibility();

		// Reset the game before leaving or before restart, in case object is not discarded
		ResetGame();

	} while (bRestartGame);

	// Reset cursor attributes to how they were before
	ConfigObjMain.bShowCursor = bShowCursorPrevious;
	SetCursorAttributes();

	// Reset colours to menu colours
	ConfigObjMain.sColourGlobal = sColourGlobalPrevFore;
	ConfigObjMain.sColourGlobalBack = sColourGlobalPrevBack;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Uninitialise Car Dodge Core
	UninitialiseCarDodgeCore();

	cls(); // Clear gameplay to not interfere with menu

	return;
}

// CarDodgeChangeUserCar
void CarDodgeMain::CarDodgeChangeUserCar() {
	// Output title
	std::cout << "\n";
	colour(LWHT, RED);
	slowcharfn(false, "~~> CAR DODGE - Change Your Car");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Display options
	OptionSelectEngine UserCarOptions;
	UserCarOptions.nSizeOfOptions = 7;
	std::string sOptions[] = {
		"Default User Car (KartCar)",
		"The Hover Rocket",
		"The Sweeper",
		"The Slicer",
		"GT Speed",
		"Xtra Aero",
		"<- Back to Main Menu"
	};
	UserCarOptions.sOptions = sOptions;

	//
	// Display graphics
	//
	CONSOLE_SCREEN_BUFFER_INFO csbiMainMenu;
	CarInfo ciMainMenuUserCar;
	short int nScreenCentre = 0;
	short int nDirectionsTextLeftColumn = 0;
	short int nDirectionsTextRightColumn = 0;

	// Set colour for cars
	colour(BLU, ConfigObjMain.sColourGlobalBack);

	// Initialise console info struct
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiMainMenu);

	// Get screen centre
	nScreenCentre = (csbiMainMenu.srWindow.Right - csbiMainMenu.srWindow.Left) / 2;

	// Get left and right columns of directions text that will come up in menu, derivin off of nScreenCentre
	nDirectionsTextLeftColumn = nScreenCentre - 29; // 26 to count for the centre column
	nDirectionsTextRightColumn = nScreenCentre + 29; // 27 is half of 54

	// Set car style
	ciMainMenuUserCar.CarStyle = CarStyles::TheSlicer;

	// Draw left car with border
	SetCursorPosition(nDirectionsTextLeftColumn - 9, 4);
	std::cout << "________";
	for (int i = 5; i < 11; i++) {
		SetCursorPosition(nDirectionsTextLeftColumn - 2, i);
		std::cout << '|';
		SetCursorPosition(nDirectionsTextLeftColumn - 9, i);
		std::cout << '|';
	}
	SetCursorPosition(nDirectionsTextLeftColumn - 9, 11);
	std::cout << "TTTTTTTT";
	ciMainMenuUserCar.bottomLeft = { (short)(nDirectionsTextLeftColumn - 7), 9 };
	RenderCar(ciMainMenuUserCar);

	// Set car style
	ciMainMenuUserCar.CarStyle = CarStyles::GTSpeed;

	// Draw right car with border
	SetCursorPosition(nDirectionsTextRightColumn + 2, 4);
	std::cout << "________";
	for (int i = 5; i < 11; i++) {
		SetCursorPosition(nDirectionsTextRightColumn + 2, i);
		std::cout << '|';
		SetCursorPosition(nDirectionsTextRightColumn + 9, i);
		std::cout << '|';
	}
	SetCursorPosition(nDirectionsTextRightColumn + 2, 11);
	std::cout << "TTTTTTTT";
	ciMainMenuUserCar.bottomLeft = { (short)(nDirectionsTextRightColumn + 4), 9 };
	RenderCar(ciMainMenuUserCar);

	// Reset colour
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Set back to original cursor position
	SetCursorPosition(0, 1);

	int nInput = UserCarOptions.OptionSelect("Please select what car you would like to use:", "", true, true, true);

	if (nInput == 1) {
		UserCar.CarStyle = CarStyles::UserCarDefault;
	}
	else if (nInput == 2) {
		UserCar.CarStyle = CarStyles::HoverRocket;
	}
	else if (nInput == 3) {
		UserCar.CarStyle = CarStyles::TheSweeper;
	}
	else if (nInput == 4) {
		UserCar.CarStyle = CarStyles::TheSlicer;
	}
	else if (nInput == 5) {
		UserCar.CarStyle = CarStyles::GTSpeed;
	}
	else if (nInput == 6) {
		UserCar.CarStyle = CarStyles::XtraAero;
	}
	else if (nInput == 7) {
		return;
	}
	else if (nInput == -1) {
		return;
	}
	else if (nInput == -2) {
		UserErrorDisplay("ERROR - An error occured when displaying the options to change cars.\nThis may be a bug with CarDodge. Please try again later.");
		std::cout << "Press any key to exit to main menu...\n";
		_getch();
		return;
	}
	else {
		UserErrorDisplay("ERROR - An unknown error occured when displaying the options to change cars. Please try again later.");
		std::cout << "Press any key to exit to main menu...\n";
		_getch();
		return;
	}

	colour(GRN, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\nCar change successful!\n");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	sleep(1000);

	return;
}

// CarDodgeInstructions
void CarDodgeMain::CarDodgeInstructions() {
	// Output title
	std::cout << "\n";
	colour(LWHT, RED);
	slowcharfn(false, "~~> CAR DODGE - How To Play");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	// Output instructions
	std::cout << "\n\n";
	slowcharCentredFn(true, "Dodge all the incoming Enemy Cars to gain points.");
	slowcharCentredFn(true, "Each car you pass, you get 1 more point.");
	slowcharCentredFn(true, "The aim of the game is to rack up as many points as you can, without crashing into any of the Enemy Cars.");
	slowcharCentredFn(true, "Press the Left Arrow key or the 'A' key to move left, and press the Right Arrow Key or the 'D' key to move right.\n");
	slowcharCentredFn(true, "You can also crash into 'good' power-up cars to gain a power-up.");
	slowcharCentredFn(true, "The power-up that is recieved can be viewed in the bottom-right corner of the game.");
	slowcharCentredFn(true, "Power-up cars look like this:");

	// Render power-up car
	sleep(500);
	CarInfo InfoCar;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo{};
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	InfoCar.CarStyle = CarStyles::PowerUpCar;
	InfoCar.bottomLeft.X = (csbiInfo.srWindow.Right - csbiInfo.srWindow.Left) / 2;
	InfoCar.bottomLeft.Y = csbiInfo.dwCursorPosition.Y + 4;
	RenderCar(InfoCar);

	sleep(500);
	colour(YLW, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\nGood luck!\n\nPress ENTER to exit to menu now...");
	std::cin.ignore((std::numeric_limits<int>::max)(), '\n');
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	return;
}

// CarDodgeHighScore
void CarDodgeMain::CarDodgeHighScore() {
	// Make sure the high score is updated before outputting
	GameHighScoresSystem::UpdateHighScoreVariables();
	SetHighScore(GameHighScoresSystem::GetCarDodgeHighScore());

	// Output title
	std::cout << "\n";
	colour(WHT, RED);
	slowcharfn(false, "~~> CAR DODGE - YOUR HIGH SCORE");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	std::cout << "\n\n\n";
	OutputBoxWithText('\n' + std::string(34 + std::to_string(GetCurrentHighScore()).length(), ' ') + '\n', RED, YLW, BLK, ConfigObjMain.sColourGlobalBack, true);

	// Set to same height as area of output in rendered box
	CONSOLE_SCREEN_BUFFER_INFO csbiHighScore;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiHighScore);
	SetCursorPosition(0, csbiHighScore.dwCursorPosition.Y - 3);

	// Output high score
	slowcharCentredFn(false, " Your current high score is... " + std::string(std::to_string(GetCurrentHighScore()).length() + 2, ' '));

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiHighScore);
	SetCursorPosition(csbiHighScore.dwCursorPosition.X - std::to_string(GetCurrentHighScore()).length() - 2, csbiHighScore.dwCursorPosition.Y);
	colour(BLU, ConfigObjMain.sColourGlobalBack);
	slowcharfn(false, std::to_string(GetCurrentHighScore()) + "!");
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	std::cout << "\n\n\n\n";
	std::cout << CentreText("Press any key to continue...") << '\n';
	_getch();

	return;
}