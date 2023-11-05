Among the Visual Studio solutions, only Visual Studio 2022 has an
up-to-date reference to the tests. The test utility (ssc-test) can
always run a full set of tests under all versions of Visual Studio.
To update tests using Visual Studio, use VS 2022.

(Note: DOS BAT files are used rather than powershell scripts because,
in some versions, setting a file's last write time to the current time
doesn't always work for me, which rather spoils update tests. The old
DOS trick of appending nothing onto a file still works a treat.)
