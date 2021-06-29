Among the Visual Studio solutions, only Visual Studio 2019 has a complete copy of the tests.
The test utility (ssc-test) can always run a full set of tests under all versions of Visual Studio.
To edit and modify tests using Visual Studio, I suggest sticking to VS 2019.

(Note: DOS BAT files are used rather than powershell scripts because the latter can be unreliable;
in particular, setting a file's last write time to the current time doesn't always work, which
rather spoils update tests. The old DOS trick of appending nothing onto a file works a treat.)
