//
// CommandHelpMessages - A file containing the functions for all the help message interfaces in the CommandsFile file, all in one central location.
//

// Help
void HelpHelp() {
	CentreColouredText(" ___HELP___ ", 1);

	std::cout << '\n';
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Lists all possible commands in ZeeTerminal.")
		<< wordWrap("\n- Displays some frequently asked questions with answers.")
		<< wordWrap("\n- Displays information about the program, such as copyright information, credits and basic program information.") << "\n\n";

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: help -h\n\n");

	return;
}

// Tutorial
void TutorialHelp() {
	CentreColouredText(" ___TUTORIAL___ ", 1);

	std::cout << '\n';
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- This command starts a short tutorial on how to use ZeeTerminal.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: tutorial -h\n\n");

	return;
}

// Cls
void ClsHelp() {
	CentreColouredText(" ___CLS___ ", 1);

	std::cout << '\n';
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- This command clears the terminal window. Nothing more, nothing less.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: cls -h\n\n");

	return;
}

// DevTools
void DevToolsHelp() {
	CentreColouredText(" ___DEVTOOLS___ ", 1);

	std::cout << '\n';
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Provides an interface to access a set of developer tools that are designed to test the features of ZeeTerminal.") << "\n\n";

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.")
		<< wordWrap("\n -1\tAutomatically starts Colour Tester.")
		<< wordWrap("\n -2\tAutomatically starts Beep Sound Test.")
		<< wordWrap("\n -3\tAutomatically starts Colour Numbers.")
		<< wordWrap("\n -4\tAutomatically starts OptionSelectEngine Tester.")
		<< wordWrap("\n -5\tAutomatically starts ScreenNavigateEngine Tester.")
		<< wordWrap("\n -6\tAutomatically starts TableEngine Tester.")
		<< wordWrap("\n -7\tAutomatically starts High-Res Nanosecond Stopwatch.")
		<< wordWrap("\n -8\tAutomatically starts ANSI VT Testing Environment.")
		<< wordWrap("\n -9\tAutomatically starts MMSYSTEM API Sound Test.")
		<< wordWrap("\n\nExample: devtools -6") << "\n\n";

	return;
}

// CpuStress
void CpuStressHelp() {
	CentreColouredText("CPUStress can stress or benchmark your CPU in multiple different ways.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Stresses your CPU and can be used for stability checks and throttling tests.")
		<< wordWrap("\n- Can benchmark your CPU to see performance metrics.") << "\n\n";

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.")
		<< wordWrap("\n -1 <rnum>\tStarts the Single Core benchmarker. You can optionally set your reiterations in place of <rnum>.")
		<< wordWrap("\n -2 <rnum>\tStarts the Multi Core benchmarker. You can optionally set your reiterations in place of <rnum>.")
		<< wordWrap("\n -3\t\tStarts the Single Core stress test.")
		<< wordWrap("\n -4\t\tStarts the Multi Core stress test.")
		<< wordWrap("\n\nExample: cpustress -1 120000") << "\n\n";

	return;
}

// Colour
void ColourHelp() {
	CentreColouredText(" ___COLOUR___ ", 1);

	std::cout << '\n';
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Adjusts the foreground colour of the terminal (text).")
		<< wordWrap("\n- Adjusts the background colour of the terminal.")
		<< wordWrap("\n- Edit and apply custom RGB colour presets.")
		<< wordWrap("\n- Resets colours to default at request.") << "\n\n";

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.")
		<< wordWrap("\n -f <colournum>\tAdjusts foreground colour. Put colour number in place of <colournum>.")
		<< wordWrap("\n -b <colournum>\tAdjusts background colour. Put desired colour number in place of <colournum>.")
		<< wordWrap("\n -r\t\tResets colours to default values (excluding RGB colour profiles).")
		<< wordWrap("\n\nExample: colour -f 3 -b 7 ") << "\n\n";
	std::cout << wordWrap("NOTE: You can get the colour numbers by executing the \"ColourNumbers\" command.") << "\n\n";

	return;
}

// Settings
void SettingsHelp() {
	CentreColouredText(" ___SETTINGS___ ", 1);

	std::cout << '\n';
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- The Settings command allows you to adjust common settings in the terminal, such as colour settings, verbosity and direction messages, and ANSI settings.") << "\n\n";

	colourSubheading();
	std::cout << "Possible arguments for the Settings command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n --highlightfore <num>\t\tModifies the highlight foreground colour. Set your colour number in place of <num>.")
		<< wordWrap("\n --highlightback <num>\t\tModifies the highlight background colour. Set your colour number in place of <num>.")
		<< wordWrap("\n --titlefore <num>\t\tModifies the title foreground colour. Set your colour number in place of <num>.")
		<< wordWrap("\n --titleback <num>\t\tModifies the title background colour. Set your colour number in place of <num>.")
		<< wordWrap("\n --subheadingfore <num>\t\tModifies the subheading foreground colour. Set your colour number in place of <num>.")
		<< wordWrap("\n --subheadingback <num>\t\tModifies the subheading background colour. Set your colour number in place of <num>.")
		<< wordWrap("\n --verbose <toggle>\t\tToggles verbose messages. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --directions <toggle>\t\tToggles direction messages. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --ansi <toggle>\t\tToggles ANSI VT sequences. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --wordwrap <toggle>\t\tToggles word wrapping. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --cursorblink <toggle>\t\tToggles cursor blinking. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --showcursor <toggle>\t\tToggles cursor visibility. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --cursorstyle <style>\t\tSets the style of the cursor. Set the style (block, underline, bar) in place of <style>.")
		<< wordWrap("\n --slowcharspeed <num>\t\tSets the speed of SlowChar. Set the speed in place of <num>.")
		<< wordWrap("\n --randcolstartup <toggle>\tToggles random colours on startup. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --customtheme <toggle>\t\tToggles terminal custom theme support. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --autocontrast <toggle>\tToggles auto-readable colour contrast. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --tempconfigdir <dir>\t\tSets a temporary custom configuration file directory. Pass the directory in place of <dir>.")
		<< wordWrap("\n --enablelogging <toggle>\tEnable all ZeeTerminal logging. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --vmessagelogging <toggle>\tEnable verbose message logging. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --usrerrorlogging <toggle>\tEnable user-space error message logging. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --commandlogging <toggle>\tEnable command input info logging. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --usrinputlogging <toggle>\tEnable user input info logging. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n --newoptionselect <toggle>\tUse the new OptionSelect Engine style. Set either true/t or false/f in place of <toggle>.")
		<< wordWrap("\n\nExample: settings --titlefore 1")
		<< wordWrap("\n\nNote: You can get colour numbers by executing the \"ColourNumbers\" command.") << "\n\n";

	return;
}

// Date
void DateHelp() {
	CentreColouredText(" ___DATE___ ", 1);

	std::cout << '\n';
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- This command displays the time and date in 24 hour time. Nothing more, nothing less.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\n")
		<< wordWrap("Example: date -h\n\n");

	return;
}

// ColourNumbers
void ColourNumbersHelp() {
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- This command displays the colour numbers for all default colours. Nothing more, nothing less.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\n")
		<< wordWrap("Example: colournumbers -h\n\n");

	return;
}

// MediaPlayer
void MediaPlayerHelp() {
	colourSubheading();
	std::cout << "What this command does: " << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Can play media and audio of specific types.")
		<< wordWrap("\n- Can view images of specific types.\n")
		<< wordWrap("\n- Supported file formats: WMA, WMV, AIFF, AU, AVI, MIDI, SND, WAV, MP3 (Only MPEG Audio Layer-3 codec), JPG and BMP.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command: " << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.")
		<< wordWrap("\n <FILE>\tOpens a file for playback/viewing. Put the exact filepath in place of <FILE>.\n\nExample: mediaplayer \"C:\\Media\\media test.mp3\"\n\n")
		<< wordWrap("\nNOTE: You need to use quotes like shown in the example to use a filename with ANY spaces.\nNOTE: Type in \"*open\" without quotes in place of the file argument to use the Windows File Dialogue to open a file.\n\n");

	return;
}

// AudioPlayer
void AudioPlayerHelp() {
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Plays a wide range of popular audio formats, such as FLAC and MP3, in an easy-to-use interface.\n- This is newer than the MediaPlayer, which uses an older DirectShow API.\n- Uses the BASS Audio API, so requires DLLs to be in the same directory as ZeeTerminal.\n- Audio formats supported: MP3, MP2, MP1, OGG, WAV, AIFF, FLAC, XM, IT, S3M, MOD, MTM, UMX, WMA, M4A, OPUS, AAC\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n <file>\tSpecify the file to use. Put the filepath in place of <file>.\n\nExample: audioplayer \"C:\\Users\\Public\\Music\\Kalimba.mp3\"\n\nNOTE: Use quotes for ANY filename with spaces inside of it, like the example.\nNOTE: Type in \"*open\" without quotes to use the Windows File Dialogue to open a file.\n\n");

	return;
}

// TTS
void TTSHelp() {
	CentreColouredText(" ___TEXT TO SPEECH___ ", 1);
	std::cout << '\n';
	CentreColouredText("Text To Speech takes in text and outputs it through the speakers in a human-like voice.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does: " << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Takes in input and outputs it with a human-like voice through the speaker.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command: " << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n <MSG>\tInput text to be said by the computer. Put text in place of <MSG>.\n\n")
		<< wordWrap("Example: tts \"The quick brown fox jumps over the lazy dog.\"\n\n")
		<< wordWrap("Note: If the text contains any spaces, put it in speech marks like the example, or it will not work.\n\n");

	return;
}

// Stopwatch
void StopwatchHelp() {
	CentreColouredText(" ___STOPWATCH___ ", 1);
	std::cout << '\n';
	CentreColouredText("This is a simple stopwatch that measures the time in seconds.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does: " << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Allows for the use for a simple stopwatch, that measures the time in seconds.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command: " << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n -i\tStarts the stopwatch immediately on command execution.\n\nExample: stopwatch -i\n\n");

	return;
}

// Read
void ReadHelp() {
	CentreColouredText(" ___READ___ ", 1);
	std::cout << '\n';
	CentreColouredText("This command outputs all contents of a file.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Reads the contents and characters of a file and outputs them to the screen.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n -b\tOutput in binary mode (std::ios_base::binary). Useful for binary files, but may cause issues and undefined behaviour.\n <file>\tThe file that will be used to read from. Put file directory in place of <file>.\n\nNOTE: You can use \"*open\" without quotes as the filename argument to use the Windows File Dialogue to get a file.\n\n")
		<< wordWrap("Example: read \"C:\\Users\\Public\\file.txt\"\n\n");

	return;
}

// Timer
void TimerHelp() {
	CentreColouredText("This is a highly accurate countdown timer that counts time in seconds.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Provides access to a highly accurate countdown timer that takes time in seconds.\n- You can press any key to exit the timer while in operation.\n\n");
	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n <time>\tAllows to pass the time in seconds as an argument. Put the number of seconds in place of <time>.\n\nExample: timer 45\n\n");

	return;
}

// Beep
void BeepHelp() {
	CentreColouredText(" ___BEEP___ ", 1);
	std::cout << "\n";
	CentreColouredText("This allows for outputting a sound at a specified frequency for a specified amount of time.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Allows for outputting a constant beep sound at a variable frequency and duration.\n- The frequency is measured in Hertz, and the duration is measured in SECONDS.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n <freq>\tSpecify the frequency as an argument. Input your frequency number in place of <freq>.\n <time>\tSpecify the time as an argument. Input your time number in place of <time>.\n\nExample: beep 500 1 (syntax: beep <freq> <time>)\n\n");

	return;
}

// MessageBox
void MessageBoxHelp() {
	CentreColouredText(" ___MESSAGEBOX___ ", 1);
	std::cout << '\n';
	CentreColouredText("This allows for creating a message box with custom icons, buttons, text and caption text.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Allows for creating a custom message box.\n- Customisations include text, caption, icon and buttons.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -t <text>\tText for the message box. Set the text in place of <text>.")
		<< wordWrap("\n -c <caption>\tCaption for the message box. Set the caption in place of <caption>.\n -i <icon>\tIcon for the message box. Set either: info, warning, error, or question, in place of <icon>.")
		<< wordWrap("\n -b <button>\tButtons for the message box. Set either: ok, okcancel, abortretryignore, yesnocancel, yesno, retrycancel, or canceltrycontinue, in place of <button>.\n\nExample: messagebox -t \"Test Text\" -c \"Test Caption\" -b ok")
		<< wordWrap("\n\nNOTE: Use speechmarks like the example when using text that contains spaces.\n\n");

	return;
}

// CopyFile
void CopyFileHelp() {
	CentreColouredText(" ___COPYFILE___ ", 1);
	std::cout << "\n";
	CentreColouredText("This command copies a file from one location to another.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Copies an existing file's contents to a file that is either new or existing.\n- This uses a directory of the source file, and the directory of the new file (NOT folder).\n- If an existing file is used as the destination file, CopyFile overwrites what is in that file with all data from the source file. Be careful when using, to ensure no loss of data occurs.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n <source>\tThe original file to be copied to another file. Put the file directory in place of <source>.\n <dest>\t\tThe file directory of the new/existing file. Put the file directory in place of <dest>.")
		<< wordWrap("\n\nExample: copyfile \"C:\\test\\a file.txt\" C:\\Users\\newfile.txt")
		<< wordWrap("\n\nNOTE: For any directory with spaces, use quotes like in the example.\nNOTE: You must have both the source and the destination directories when using them as arguments.\nNOTE: Read this article for information on the different forms of filepaths: ");

	colour(LBLU, ConfigObjMain.sColourGlobalBack);
	std::cout << "https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file#fully-qualified-vs-relative-paths" << "\n\n";
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	return;
}

// Copy
void CopyHelp() {
	CentreColouredText(" ___COPY___ ", 1);
	std::cout << '\n';
	CentreColouredText("This command copies a file from one location to a destination directory.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Copies a file from one location to another location/directory.\n- This uses a directory of the file, and the directory of the destination location folder (NOT file).\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -o\t\tEnable overwrite mode. Any existing file with the same filename as the file to copy will be overwritten when specified."
		"\n -d\t\tEnable folder copy mode. When a folder is specified as a source, the contents of that folder will be recursively copied to the destination."
		"\n <source>\tThe file to copy. Put the file directory in place of <source>.\n <dest>\t\tThe destination location/directory. Put the directory path in place of <dest>.\n\n"
		"Example: copy \"C:\\test\\a file.txt\" C:\\Users\n\n"
		"NOTE: For any directory with spaces, use quotes like in the example.\nNOTE: You must have both the source and the destination directories when using them as arguments.\nNOTE: Read this article for information on the different forms of filepaths: ");
	
	colour(LBLU, ConfigObjMain.sColourGlobalBack);
	std::cout << "https://learn.microsoft.com/en-us/windows/win32/fileio/naming-a-file#fully-qualified-vs-relative-paths" << "\n\n";
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);

	return;
}

// TextInfo
void TextInfoHelp() {
	CentreColouredText(" ___TEXTINFO___ ", 1);
	std::cout << '\n';
	CentreColouredText("This allows for displaying information about a string of text.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Displays information about a string of text.\n- This can include words, sentences, letters, characters, etc.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n <text>\tThe text to be used for the command. Put the text in place of <text>.")
		<< wordWrap("\n\nExample: textinfo \"The quick brown fox jumps over the lazy dog.\"\n\nNOTE: Use quotes for text with any spaces in it like the example, or the text may not be read properly.\n\n");

	return;
}

// ConfigAction
void ConfigActionHelp() {
	std::cout << '\n';
	CentreColouredText(" ___CONFIGACTION___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Contains options to interact with the ZeeTerminal Configuration File System.\n- You can manually read, write, create and display config files/objects with this command.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\t\tDisplays this help message.\n --readconfigfile\tReads from the currently-pointed configuration file\n --writeconfigfile\tWrites to the currently-pointed-to configuration file.")
		<< wordWrap("\n --createconfigfile\tCreates a configuration file to the same file directory as user-set location, or default location as fallback.\n --displayconfigobj\tDisplays contents of the main configuration object in memory.")
		<< wordWrap("\n --displayconfigfile\tDisplays contents of currently-pointed-to configuration file.\n\nExample: configaction --readconfigfile\n\n");

	return;
}

// BeepSounds
void BeepSoundsHelp() {
	CentreColouredText(" ___BEEPSOUNDS___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Provides an interface to play different themes, songs and sounds with beeps.\n- This uses the MMSYSTEM API to play beep sounds.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\t\tDisplays this help message.\n --misssionimpossible\tPlays a small snippet of the Mission Impossible theme song.")
		<< wordWrap("\n --happybirthday\tPlays the Happy Birthday song.\n --supermario\t\tPlays the Super Mario Theme Song.\n --dundundun\t\tPlays a 'dun dun dun dun' sound.")
		<< wordWrap("\n --imperialmarch\tPlays the Star Wars Imperial March song.\n --tetris\t\tPlays the Tetris Theme Song.\n --dramatic\t\tPlays a dramatic song.\n --rickroll\t\tPlays the RickRoll song (a portion of Rick Astley's 'Never Gonna Give You Up')\n\nExample: beepsounds --missionimpossible\n\n");

	return;
}

// RickRoll
void RickRollHelp() {
	std::cout << '\n';
	CentreColouredText(" ___RICKROLL___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Rickrolls a ZeeTerminal user (a decade-old meme).\n- This only works when the user is online and connected to the Internet.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: rickroll -h\n\n");

	return;
}

// ShellExecute
void ShellExecuteHelp() {
	CentreColouredText("___SHELLEXECUTE___", 1);
	std::cout << "\n";
	CentreColouredText("This allows for the execution of CMD shell commands from ZeeTerminal.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Forwards and executes commands in the Windows Command Prompt.\n- You can perform actions such as opening a specific file or performing an operation of sorts.\n- Use when you know what you are doing.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n <command>\tCommand to execute. Put the desired command in place of <command>.\n\nExample: ShellExecute \"ipconfig -a\"")
		<< wordWrap("\n\nNOTE: Use quotes whenever there are spaces in the command, like the example.\n\n");

	return;
}

// Hacker
void HackerHelp() {
	CentreColouredText(" ___HACKER___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Displays text of random numbers to make the computer look like it's processing a hacking script.\n- Allows you to type like a hacker, with the ability to use a custom file to do so.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -i\t\tStart immediately, with default settings when no argument is given.\n --display\tStarts the hacking text part of this command.\n --type\t\tStarts the hacker typing part of this command.\n --typecustom\tStarts the hacker typing part of this command, with custom file output abilities.\n <speed>\tSpeed of output characters for 'type' and 'typecustom' arguments. Must be a number.\n <filepath>\tCustom filepath argument for 'typecustom' argument. Must be a valid filepath.")
		<< wordWrap("\n\nSyntax for '--type' argument:\t\t --type <speed>\nSyntax for '--typecustom' argument:\t --typecustom <filepath> <speed> (In order)")
		<< wordWrap("\n\nExample: hacker --type\n\n");

	return;
}

// Calculator
void CalculatorHelp() {
	CentreColouredText(" ___CALCULATOR___ ", 1);
	std::cout << "\n";
	CentreColouredText("This allows for advanced BIDMAS calculations to be computed fully offline.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Calculates a string-based calculation, using the BIDMAS order of operations.\n- Supports up to a theoretical 18 trillion characters per calculation string.\n- Supports all BIDMAS operations, trigonometric functions, mathematical constants and square/cube roots.\n- Can display how the answer was worked out.\n\n");

	colourSubheading();
	std::cout << "___Syntax___:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Type in any symbol or function from the following in your calculation input:\n\n");

	colour(LCYN, ConfigObjMain.sColourGlobalBack);
	std::cout << "___BASIC MATHEMATICAL OPERATORS___";
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << "\n\t --> '/': Division\n\t --> '*': Multiplication\n\t --> '+': Addition\n\t --> '-': Subtraction\n\t --> '^': To the power of\n\n";

	colour(LBLU, ConfigObjMain.sColourGlobalBack);
	std::cout << "___SQUARE/CUBE ROOT AND TRIGONOMETRY___";
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap(std::string("\n\t --> 'sqrt(n)': Square Root function, where n is the desired number\n\t --> 'cbrt(n)': Cube Root function, where n is the desired number\n\t --> 'sin(n)': Sine function, where n is the desired number")
		+ "\n\t --> 'cos(n)': Cosine function, where n is the desired number\n\t --> 'tan(n)': Tangent function, where n is the desired number\n\t --> 'asin(n)': Arc Sine function, where n is the desired number"
		+ "\n\t --> 'acos(n)': Arc Cosine function, where n is the desired number\n\t --> 'atan(n)': Arc Tangent function, where n is the desired number\n\n");

	colour(GRN, ConfigObjMain.sColourGlobalBack);
	std::cout << "___MATHEMATICAL CONSTANTS___";
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << "\n\t --> '(pi)': The PI number constant.\n\t --> '(e)': The Euler's number constant.\n\n";

	colour(LMAG, ConfigObjMain.sColourGlobalBack);
	std::cout << "___OTHER___";
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n\t --> '(ans)': The 'Ans' user-space variable (last calculated answer)\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n -w\tMakes calculator display working out steps.\n -n\tMakes calculator NOT display working out steps. This is default when no -n or -w argument is passed AND there is a calculation string argument passed.\n -e\tUse European number notation (',' for decimal point, '.' for thousands separator).\n <calc>\tCalculation as an argument. Input your calculation in place of <calc>.")
		<< wordWrap("\n\nExample: calculator (10+5^2)((5*-2)+9-3^3)/2\n\n");

	return;
}

// Logoff
void LogoffHelp() {
	CentreColouredText(" ___LOGOFF___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Logs off the current user from the computer.\n- Initiating the logoff process happens immediately and on command.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: logoff -h\n\n");

	return;
}

// Shutdown
void ShutdownHelp() {
	CentreColouredText(" ___SHUTDOWN___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Shuts down the computer that ZeeTerminal is running on.\n- It can be set to trigger after a certain amount of time.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -t <time>\tA time argument for shutdown in seconds. Put time argument in place of <time>. Must be a number.\n -c\t\tCancel any pending shutdown operations.")
		<< wordWrap("\n\nExample: shutdown -t 5\n\n");

	return;
}

// Reboot
void RebootHelp() {
	CentreColouredText(" ___REBOOT___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Reboots the computer that ZeeTerminal is running on.\n- It can be set to trigger after a certain amount of time.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -t <time>\tA time argument for reboot in seconds. Put time argument in place of <time>. Must be a number.\n -c\t\tCancel any pending reboot operations.")
		<< wordWrap("\n\nExample: reboot -t 5\n\n");

	return;
}

// Hibernate
void HibernateHelp() {
	CentreColouredText(" ___HIBERNATE___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Hibernates the computer that ZeeTerminal is running on.\n- Initiating the hibernate process is immediate and on command.\n- Hibernation will NOT work if hibernation is disabled on the computer running ZeeTerminal.\n\n");

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: hibernate -h\n\n");

	return;
}

// ResetExpl
void ResetExplHelp() {
	CentreColouredText(" ___RESETEXPL___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Resets explorer.exe on the system running ZeeTerminal.\n- The reset process executes immediately and on command.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: resetexpl -h\n\n");

	return;
}

// MemTest
void MemTestHelp() {
	CentreColouredText(" ___MEMTEST___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Checks your computer's memory to see if any issues arise with it.\n- The way this is done is by filling up the computer's memory and assigning each byte of memory with a specific value.")
		<< wordWrap("\n- There are 2 methods of checking: A quick round of x binary searches using randomly calculated numbers, and a slower x-pass linear search that checks every cell of assigned memory for the correct value (x being no. of passes).")
		<< wordWrap("\n- Any program/system crash or completely unexpected behaviour in this test probably means that the memory is faulty.\n- It is recommended that all programs and background tasks are closed before any memory tests are run.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -f\t\tSimply fill up and allocate the system memory, and then deallocate.\n -b <passes>\tPerform binary searches on allocated memory. Put number of passes in place of <passes>.")
		<< wordWrap("\n -l <passes>\tPerform linear check searches on allocated memory. Put number of passes in place of <passes>.\n -e <passes>\tPerform extended linear check searches on allocated memory. Put number of passes in place of <passes>.\n -k\t\tRequire a keypress before memory deallocation, with the -f option. Default is false.")
		<< wordWrap("\n -m\t\tUse multithreading. May increase performance but can increase CPU temperatures.\n -a\t\tUse all the memory available on the host system, rather than just the default available memory. May not work with systems that have paging disabled.\n\nExample: memtest -k -l 6\n\n");

	return;
}

// RandCol
void RandColHelp() {
	CentreColouredText(" ___RANDCOL___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Picks randomised colours from the colour numbers, and sets them as default.\n- Make sure you set a colour preset for your current colours before running this command, so you don't lose them.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: randcol -h\n\n");

	return;
}

// Pause
void PauseHelp() {
	CentreColouredText(" ___PAUSE___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Pauses the operation of ZeeTerminal and resumes on any user keypress.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n -e\tRequire an ENTER keypress only, instead of any key being allowed.\n\nExample: pause -h\n\n");

	return;
}

// CommandNum
void CommandNumHelp() {
	CentreColouredText(" ___COMMANDNUM___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Displays the number of inputted commands since the startup of the current ZeeTerminal session.\n- Also displays the number of successful and unsuccessful commands.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: commandnum -h\n\n");

	return;
}

// SlowChar
void SlowCharHelp() {
	CentreColouredText(" ___SLOWCHAR___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Takes in text and outputs it in a slow character manner.\n- You can choose to output in random colours, as well.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n -r\tOutput slow character text in random colours.\n <text>\tThe text to be used for the command. Put text in place of <text>.")
		<< wordWrap("\n\nExample: slowchar -r \"The quick brown fox jumps over the lazy dog.\"\n\nNOTE: Use quotes, like in the example, for any text that contains spaces.\n\n");

	return;
}

// ReverseText
void ReverseTextHelp() {
	CentreColouredText(" ___REVERSETEXT___ ", 1);
	std::cout << '\n';

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Outputs text that is inputted in reverse.\n- Can be outputted with a slow character effect.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n -s\tOutputs reverse text with a slow character effect.\n <text>\tThe text to be outputted in reverse. Put the desired text in place of <text>.")
		<< wordWrap("\n\nExample: reversetext -s \"The quick brown fox jumps over the lazy dog.\"\n\nNOTE: Use quotes, like in the example, for any text argument that contains spaces.\n\n");

	return;
}

// Notes
void NotesHelp() {
	CentreColouredText(" ___NOTES___ ", 1);
	std::cout << '\n';
	CentreColouredText("Allows for the management and creation of custom notes.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Allows the taking-down and saving of notes that can be accessed from this program.\n- The notes are saved on memory and on a file in the same directory as ZeeTerminal.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\t\tDisplays this help message.\n -a <note>\t\tAdd a note. Put the desired note in place of <note>.\n -r <linenum>\t\tRemove a note indicated by <linenum> from the notes. Put the line number in place of <linenum>. Cannot be less than 1 or more than the number of saved notes. If there is no line number argument, the last line will be removed.")
		<< wordWrap("\n -e\t\t\tEdit all notes in notes array.\n -m <linenum> <text>\tModify a note indicated by the line number. Put the line number in place of <linenum>, or leave it blank to modify the last line. Put the desired note text in place of <text>.\n -o\t\t\tOutput all notes that are saved.\n -c\t\t\tClear all notes, permanently.\n -u\t\t\tUpdate the Notes array (memory notes) with the Notes file. This will take effect immediately.\n -f\t\t\tUpdate the Notes file with the Notes array (memory notes). This will take effect immediately.")
		<< wordWrap("\n\nExample: notes -a \"The quick brown fox jumps over the lazy dog.\"\n\nNOTE: Use quotes, like the example, for any text that contains spaces.\n\n");

	return;
}

// FileParse
void FileParseHelp() {
	CentreColouredText(" ___FILEPARSE___ ", 1);
	std::cout << '\n';
	CentreColouredText("This allows you to run scripts in ZeeTerminal, as if it was an interpreter.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Allows for running scripts in ZeeTerminal, as if it was an interpreter.\n- Commands get run exactly the same way as if a user runs them.\n- The parsed lines only get run from the command input screen (where it says \"Command: >\"), and nowhere else do they get substituted.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -e\t\tExit ZeeTerminal on script completion.\n --exit\t\tSame as the '-e' option.\n <filepath>\tFilepath of script to run. Put filepath in place of <filepath>.\n\n");
	std::cout << wordWrap("Example: fileparse --exit \"C:\\Users\\Public\\some folder\\test script.txt\"\n\nNOTE: Just like the example, when using any filepath with spaces, enclose it with quotes.\n\n");

	return;
}

// Disp
void DispHelp() {
	CentreColouredText(" ___DISP___ ", 1);
	std::cout << "\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- This command allows you to turn command interface output on or off.\n"
		"- The command interface is the starting screen where the \"Command: > \" text is shown.\n"
		"- This command also, when executing scripts, disables outputting the command that is about to run.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\tDisplays this help message.\n -y  OR  --on\tEnable DISP, where the command interface output text is displayed.\n"
		" -n  OR  --off\tDisable DISP, where the command interface output text is hidden and not displayed.\n\nExample: disp --off\n\n");

	return;
}

// SysInfo
void SysInfoHelp() {
	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Displays system information about the system that this ZeeTerminal session is currently running on.\n- Displays information such as processor, OS version, OS build and memory information.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n\nExample: sysinfo -h\n\n");

	return;
}

// Einstein
void EinsteinHelp() {
	CentreColouredText(" ___EINSTEIN___ ", 1);
	std::cout << "\n";
	CentreColouredText("Outputs one of 50 quotes narrated by the famous Albert Einstein.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Outputs one of 50 hard-coded quotes that were narrated by Albert Einstein.\n- Quotes are picked and outputted in complete randomness.\n"
		"- You can choose to output in random colours, and/or in slow characters.\n\n");


	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n -c\tOutput the quote in random foreground colours.\n -s\tOutput the quote in a slow-character format.\n\nExample: einstein -s -c\n\n");

	return;
}

// Edison
void EdisonHelp() {
	CentreColouredText(" ___EDISON___ ", 1);
	std::cout << "\n";
	CentreColouredText("Outputs one of 50 quotes narrated by the famous Thomas Edison.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Outputs one of 50 hard-coded quotes that were narrated by Thomas Edison.\n- Quotes are picked and outputted in complete randomness.\n"
		"- You can choose to output in random colours, and/or in slow characters.\n\n");


	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n -c\tOutput the quote in random foreground colours.\n -s\tOutput the quote in a slow-character format.\n\nExample: edison -s -c\n\n");

	return;
}

// Tesla
void TeslaHelp() {
	CentreColouredText(" ___TESLA___ ", 1);
	std::cout << "\n";
	CentreColouredText("Outputs one of 50 quotes narrated by the famous Nikola Tesla.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- Outputs one of 50 hard-coded quotes that were narrated by Nikola Tesla.\n- Quotes are picked and outputted in complete randomness.\n"
		"- You can choose to output in random colours, and/or in slow characters.\n\n");


	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\tDisplays this help message.\n -c\tOutput the quote in random foreground colours.\n -s\tOutput the quote in a slow-character format.\n\nExample: tesla -s -c\n\n");

	return;
}

// Cow
void CowHelp() {
	CentreColouredText(" ___COW___ ", 1);
	std::cout << "\n";
	CentreColouredText("This command allows for outputting an ASCII cow in multiple ways.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- This command outputs an ASCII cow, with options for allowing the cow to say quotes or text.\n- You can choose to also output the cow in a colourful manner.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\t\tDisplays this help message.\n -o\t\t\tOutputs a simple cow, with no extra text.\n --saytext <text>\tMake the cow 'say' specified text. Put the text in place of <text>."
		"\n --quote\t\tMake the cow say a random quote from Nikola Tesla, Albert Einstein or Thomas Edison.\n -c\t\t\tOutput the cow in a randomised colour.\n\n"
		"Example: cow --saytext \"Hello, I am a cow\"\n\nNOTE: Please make sure that when using spaces in the <text> argument with --saytext, use quotes (\"\").\n\n");

	return;
}

// Cat
void CatHelp() {
	CentreColouredText(" ___CAT___ ", 1);
	std::cout << "\n";
	CentreColouredText("This command allows for outputting an ASCII cat in multiple ways.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- This command outputs an ASCII cat, with options for allowing the cat to say quotes or text.\n- You can choose to also output the cat in a colourful manner.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\t\tDisplays this help message.\n -o\t\t\tOutputs a simple cat, with no extra text.\n --saytext <text>\tMake the cat 'say' specified text. Put the text in place of <text>."
		"\n --quote\t\tMake the cat say a random quote from Nikola Tesla, Albert Einstein or Thomas Edison.\n -c\t\t\tOutput the cat in a randomised colour.\n\n"
		"Example: cat --saytext \"Hello, I am a cat\"\n\nNOTE: Please make sure that when using spaces in the <text> argument with --saytext, use quotes (\"\").\n\n");

	return;
}

// Bunny
void BunnyHelp() {
	CentreColouredText(" ___BUNNY___ ", 1);
	std::cout << "\n";
	CentreColouredText("This command allows for outputting an ASCII bunny in multiple ways.", 2);
	std::cout << "\n\n";

	colourSubheading();
	std::cout << "What this command does:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n- This command outputs an ASCII bunny, with options for allowing the bunny to say quotes or text.\n- You can choose to also output the bunny in a colourful manner.\n\n");

	colourSubheading();
	std::cout << "Possible arguments for this command:" << NOULINE_STR;
	colour(ConfigObjMain.sColourGlobal, ConfigObjMain.sColourGlobalBack);
	std::cout << wordWrap("\n -h\t\t\tDisplays this help message.\n -o\t\t\tOutputs a simple bunny, with no extra text.\n --saytext <text>\tMake the bunny 'say' specified text. Put the text in place of <text>."
		"\n --quote\t\tMake the bunny say a random quote from Nikola Tesla, Albert Einstein or Thomas Edison.\n -c\t\t\tOutput the bunny in a randomised colour.\n\n"
		"Example: bunny --saytext \"Hello, I am a bunny\"\n\nNOTE: Please make sure that when using spaces in the <text> argument with --saytext, use quotes (\"\").\n\n");

	return;
}