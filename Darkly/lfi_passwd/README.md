# Local File Intrusion

## Exploit
[OWASP](https://owasp.org/www-project-web-security-testing-guide/v42/4-Web_Application_Security_Testing/07-Input_Validation_Testing/11.1-Testing_for_Local_File_Inclusion)

Let's consider a typical URL on the website, for instance `http://${URL}/index.php?page=survey`. What if instead of survey we tried reading files outside of the webserver directory?

The most obvious target is `/etc/passwd/`. Trying to access it via for instance `http://${URL}/index.php?page=../../etc/passwd` we get discouraging console.log message. Said messages change the deeper we go, showing us that the darkly iso is just merely emulating the vulnerability. So be it, we perserve until finding the right path, `http://${URL}/index.php?page=../../../../../../../etc/passwd`

##Fix
The most effective fix would be to prevent user input over included files or using a whitelist of allowed files. Running the webserver in a private namespace(container) could act as a stopgap on top of these fixes.
