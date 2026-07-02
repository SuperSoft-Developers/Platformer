#include <3ds.h>
#include <stdio.h>
#include <string.h>

int main() {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);

    u8 colorToggle = 0;

    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();

        // sair
        if (kDown & KEY_START) break;

        // alterna cor com A
        if (kDown & KEY_A) {
            colorToggle = !colorToggle;
        }

        // pega framebuffer superior
        u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);

        int width = 240 * 3;   // RGB888 simplificado
        int height = 400;

        u8 r = colorToggle ? 255 : 0;
        u8 b = colorToggle ? 0 : 255;

        // pinta tela inteira
        for (int i = 0; i < width * height; i += 3) {
            fb[i + 0] = r; // R
            fb[i + 1] = 0; // G
            fb[i + 2] = b; // B
        }

        consoleClear();
        printf("BerDev says hi!\n");
        printf("Press A to change color\n");
        printf("START to exit\n");

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
