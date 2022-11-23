bool main(void)

{
    int32_t aiStack20 [4];

    sym.imp.puts("***********************************");
    sym.imp.puts("* \t     -Level00 -\t\t  *");
    sym.imp.puts("***********************************");
    sym.imp.printf("Password:");
    sym.imp.__isoc99_scanf(0x8048636, aiStack20);
    if (aiStack20[0] != 0x149c) {
        sym.imp.puts("\nInvalid Password!");
    }
    else {
        sym.imp.puts("\nAuthenticated!");
        sym.imp.system("/bin/sh");
    }
    return aiStack20[0] != 0x149c;
}
