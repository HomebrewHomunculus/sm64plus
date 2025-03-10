#include <ultra64.h>

#include "area.h"
#include "save_file.h"

// DirectInput keyboard scan codes (from https://gist.github.com/tracend/912308)

#define DIK_ESCAPE          0x01
#define DIK_1               0x02
#define DIK_2               0x03
#define DIK_3               0x04
#define DIK_4               0x05
#define DIK_5               0x06
#define DIK_6               0x07
#define DIK_7               0x08
#define DIK_8               0x09
#define DIK_9               0x0A
#define DIK_0               0x0B
#define DIK_MINUS           0x0C    /* - on main keyboard */
#define DIK_EQUALS          0x0D
#define DIK_BACK            0x0E    /* backspace */
#define DIK_TAB             0x0F
#define DIK_Q               0x10
#define DIK_W               0x11
#define DIK_E               0x12
#define DIK_R               0x13
#define DIK_T               0x14
#define DIK_Y               0x15
#define DIK_U               0x16
#define DIK_I               0x17
#define DIK_O               0x18
#define DIK_P               0x19
#define DIK_LBRACKET        0x1A
#define DIK_RBRACKET        0x1B
#define DIK_RETURN          0x1C    /* Enter on main keyboard */
#define DIK_LCONTROL        0x1D
#define DIK_A               0x1E
#define DIK_S               0x1F
#define DIK_D               0x20
#define DIK_F               0x21
#define DIK_G               0x22
#define DIK_H               0x23
#define DIK_J               0x24
#define DIK_K               0x25
#define DIK_L               0x26
#define DIK_SEMICOLON       0x27
#define DIK_APOSTROPHE      0x28
#define DIK_GRAVE           0x29    /* accent grave */
#define DIK_LSHIFT          0x2A
#define DIK_BACKSLASH       0x2B
#define DIK_Z               0x2C
#define DIK_X               0x2D
#define DIK_C               0x2E
#define DIK_V               0x2F
#define DIK_B               0x30
#define DIK_N               0x31
#define DIK_M               0x32
#define DIK_COMMA           0x33
#define DIK_PERIOD          0x34    /* . on main keyboard */
#define DIK_SLASH           0x35    /* / on main keyboard */
#define DIK_RSHIFT          0x36
#define DIK_MULTIPLY        0x37    /* * on numeric keypad */
#define DIK_LMENU           0x38    /* left Alt */
#define DIK_SPACE           0x39
#define DIK_CAPITAL         0x3A
#define DIK_F1              0x3B
#define DIK_F2              0x3C
#define DIK_F3              0x3D
#define DIK_F4              0x3E
#define DIK_F5              0x3F
#define DIK_F6              0x40
#define DIK_F7              0x41
#define DIK_F8              0x42
#define DIK_F9              0x43
#define DIK_F10             0x44
#define DIK_NUMLOCK         0x45
#define DIK_SCROLL          0x46    /* Scroll Lock */
#define DIK_NUMPAD7         0x47
#define DIK_NUMPAD8         0x48
#define DIK_NUMPAD9         0x49
#define DIK_SUBTRACT        0x4A    /* - on numeric keypad */
#define DIK_NUMPAD4         0x4B
#define DIK_NUMPAD5         0x4C
#define DIK_NUMPAD6         0x4D
#define DIK_ADD             0x4E    /* + on numeric keypad */
#define DIK_NUMPAD1         0x4F
#define DIK_NUMPAD2         0x50
#define DIK_NUMPAD3         0x51
#define DIK_NUMPAD0         0x52
#define DIK_DECIMAL         0x53    /* . on numeric keypad */
#define DIK_OEM_102         0x56    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
#define DIK_F11             0x57
#define DIK_F12             0x58
#define DIK_F13             0x64    /*                     (NEC PC98) */
#define DIK_F14             0x65    /*                     (NEC PC98) */
#define DIK_F15             0x66    /*                     (NEC PC98) */
#define DIK_KANA            0x70    /* (Japanese keyboard)            */
#define DIK_ABNT_C1         0x73    /* /? on Brazilian keyboard */
#define DIK_CONVERT         0x79    /* (Japanese keyboard)            */
#define DIK_NOCONVERT       0x7B    /* (Japanese keyboard)            */
#define DIK_YEN             0x7D    /* (Japanese keyboard)            */
#define DIK_ABNT_C2         0x7E    /* Numpad . on Brazilian keyboard */
#define DIK_NUMPADEQUALS    0x8D    /* = on numeric keypad (NEC PC98) */
#define DIK_PREVTRACK       0x90    /* Previous Track (DIK_CIRCUMFLEX on Japanese keyboard) */
#define DIK_AT              0x91    /*                     (NEC PC98) */
#define DIK_COLON           0x92    /*                     (NEC PC98) */
#define DIK_UNDERLINE       0x93    /*                     (NEC PC98) */
#define DIK_KANJI           0x94    /* (Japanese keyboard)            */
#define DIK_STOP            0x95    /*                     (NEC PC98) */
#define DIK_AX              0x96    /*                     (Japan AX) */
#define DIK_UNLABELED       0x97    /*                        (J3100) */
#define DIK_NEXTTRACK       0x99    /* Next Track */
#define DIK_NUMPADENTER     0x9C    /* Enter on numeric keypad */
#define DIK_RCONTROL        0x9D
#define DIK_MUTE            0xA0    /* Mute */
#define DIK_CALCULATOR      0xA1    /* Calculator */
#define DIK_PLAYPAUSE       0xA2    /* Play / Pause */
#define DIK_MEDIASTOP       0xA4    /* Media Stop */
#define DIK_VOLUMEDOWN      0xAE    /* Volume - */
#define DIK_VOLUMEUP        0xB0    /* Volume + */
#define DIK_WEBHOME         0xB2    /* Web home */
#define DIK_NUMPADCOMMA     0xB3    /* , on numeric keypad (NEC PC98) */
#define DIK_DIVIDE          0xB5    /* / on numeric keypad */
#define DIK_SYSRQ           0xB7
#define DIK_RMENU           0xB8    /* right Alt */
#define DIK_PAUSE           0xC5    /* Pause */
#define DIK_HOME            0xC7    /* Home on arrow keypad */
#define DIK_UP              0xC8    /* UpArrow on arrow keypad */
#define DIK_PRIOR           0xC9    /* PgUp on arrow keypad */
#define DIK_LEFT            0xCB    /* LeftArrow on arrow keypad */
#define DIK_RIGHT           0xCD    /* RightArrow on arrow keypad */
#define DIK_END             0xCF    /* End on arrow keypad */
#define DIK_DOWN            0xD0    /* DownArrow on arrow keypad */
#define DIK_NEXT            0xD1    /* PgDn on arrow keypad */
#define DIK_INSERT          0xD2    /* Insert on arrow keypad */
#define DIK_DELETE          0xD3    /* Delete on arrow keypad */
#define DIK_LWIN            0xDB    /* Left Windows key */
#define DIK_RWIN            0xDC    /* Right Windows key */
#define DIK_APPS            0xDD    /* AppMenu key */
#define DIK_POWER           0xDE    /* System Power */
#define DIK_SLEEP           0xDF    /* System Sleep */
#define DIK_WAKE            0xE3    /* System Wake */
#define DIK_WEBSEARCH       0xE5    /* Web Search */
#define DIK_WEBFAVORITES    0xE6    /* Web Favorites */
#define DIK_WEBREFRESH      0xE7    /* Web Refresh */
#define DIK_WEBSTOP         0xE8    /* Web Stop */
#define DIK_WEBFORWARD      0xE9    /* Web Forward */
#define DIK_WEBBACK         0xEA    /* Web Back */
#define DIK_MYCOMPUTER      0xEB    /* My Computer */
#define DIK_MAIL            0xEC    /* Mail */
#define DIK_MEDIASELECT     0xED    /* Media Select */

char* gTitleString = "Super Mario 64 Plus v1.0.1";

s8 configFullscreen = 1;
unsigned int configCustomFullscreenResolution = 0;
unsigned int configFullscreenWidth = 1920;
unsigned int configFullscreenHeight = 1080;
unsigned int configFullscreenRefreshRate = 60;
unsigned int configWindowWidth = 1280;
unsigned int configWindowHeight = 720;
s8 configCustomInternalResolution = 0;
unsigned int configInternalResolutionWidth = 3840;
unsigned int configInternalResolutionHeight = 2160;

float configSeqVolume[] = {1, 1, 1};

// TODO (Mors): Rename these with a config prefix.
s8 g60FPS = 1;
s8 gDisableDrawDistance = 1;
float gDrawDistanceMultiplier = 1.0f;
s8 gDisableLowPoly = 1;
unsigned int gNoiseType = 0;
s8 configForce4by3 = 0;

s8 gImprovedControls = 1;
s8 gBackwardSpeedCap = 1;
s8 gDpadControls = 1;
s8 gFullAirControl = 0;
s8 gDisableBLJ = 0;
s8 gDisableFallDamage = 0;

s8 gFixVariousBugs = 1;
s8 gRespawnBlueCoinSwitch = 1;
s8 gRemoveAnnoyingWarps = 1;
// TODO (Mors): Turn this into a "updated powerups" option eventually.
// Vanish Mario would fall slower, and Wing Mario would have completely revamped flying.
s8 gImprovedMetalCap = 1;
s8 gDisableBooDialogue = 1;
s8 gTalkEasier = 1;
s8 gQuitOption = 1;
unsigned int gStayInLevel = 0;
s8 gSkipStarSelect = 0;
s8 gRestartLevelAfterStar = 0;
s8 gLeaveAnyTime = 0;
s8 gVisibleSecrets = 0;
s8 gFlexibleCannons = 0;
s8 gSkipCutscenes = 0;

s8 gImprovedCamera = 1;
s8 gCenterCameraButton = 1;
unsigned int gManualCamera = 0;
s8 gSmarterManualCamera = 0;
s8 gInvertedCamera = 0;
float gCameraSpeed = 32.0f;
float gAdditionalCameraDistance = 0.0f;
float gAdditionalFOV = 0.0f;

unsigned int gHudStyle = 2;
s8 gCenterHud = 0;
s8 gHUDFiltering = 0;
unsigned int gHUDUpscaling = 0;
s8 gHudStars = 0;
s8 gShow100CoinStar = 0;
s8 gAlwaysShowHealth = 0;
s8 gHideHud = 0;

s8 gWallSliding = 1;
s8 gGroundPoundJump = 0;
s8 gSunshineDive = 0;
s8 gOdysseyDive = 0;
s8 gFlashbackPound = 0;

s8 gPyramidCutscene = 1;
s8 gTrapdoorSound = 1;
s8 gTwirlTripleJump = 0;
s8 gSpawnSparkles = 0;
s8 gReplaceKeysWithStars = 0;

s8 gLifeMode = 0;
s8 gEncoreMode = 0;
s8 gGreenDemon = 0;
s8 gHardSave = 0;
s8 gDaredevilSave = 0;
s8 gHardcoreSave = 0;

s8 gFXMode = 0;
s8 gDisableLighting = 0;
s8 gForceLowPoly = 0;
s8 gNearestNeighbor = 0;

s8 gDebugMovementMode = 0;
s8 gDebugCapChanger = 0;
s8 gVerticalCamera = 0;
unsigned int gTextureUpscaling = 0;

unsigned int configButtonA = A_BUTTON;
unsigned int configButtonB = Z_TRIG;
unsigned int configButtonX = B_BUTTON;
unsigned int configButtonY = 0;
unsigned int configButtonStart = START_BUTTON;
unsigned int configButtonSelect = L_TRIG;
unsigned int configButtonL = Z_TRIG;
unsigned int configButtonR = R_TRIG;
unsigned int configButtonZL = Z_TRIG;
unsigned int configButtonZR = R_TRIG;
unsigned int configButtonThumbLeft = 0;
unsigned int configButtonThumbRight = L_TRIG;
unsigned int gControllerDeadzone = 512;

unsigned int configKeyA = DIK_L;
unsigned int configKeyB = DIK_COMMA;
unsigned int configKeyStart = DIK_SPACE;
unsigned int configKeyL = DIK_C;
unsigned int configKeyR = DIK_RSHIFT;
unsigned int configKeyZ = DIK_K;
unsigned int configKeyCUp = 0x0148;
unsigned int configKeyCDown = 0x0150;
unsigned int configKeyCLeft = 0x014B;
unsigned int configKeyCRight = 0x014D;
unsigned int configKeyStickUp = DIK_W;
unsigned int configKeyStickDown = DIK_S;
unsigned int configKeyStickLeft = DIK_A;
unsigned int configKeyStickRight = DIK_D;

// These probably don't belong here, but I don't have a better place for them at the moment.
// TODO (Mors): Move this out to somewhere that fits.
s16 gCollectedStar = 0;

s8 stay_in_level() {
    if (gStayInLevel == 2 && (
    // If we have collected the first star in the first act in these levels, kick us out.
    (gCurrActNum == 1 && gCollectedStar == 0 &&
    (gCurrLevelNum == LEVEL_BOB || gCurrLevelNum == LEVEL_WF || gCurrLevelNum == LEVEL_JRB || gCurrLevelNum == LEVEL_BBH || 
    gCurrLevelNum == LEVEL_CCM || gCurrLevelNum == LEVEL_TTM || gCurrLevelNum == LEVEL_SSL || 
    // In addition to all of above, kick us only if the submarine is there in DDD.
    ((!(save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_2 | SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR))) && gCurrLevelNum == LEVEL_DDD))) ||
    // Kick us from the lonely mushroom in TTM as well.
    (gCollectedStar == 5 && gCurrLevelNum == LEVEL_TTM) ||
    // If we have collected any stars in any sublevels except for these, kick us again.
    (gCurrAreaIndex > 1 && gCurrLevelNum != LEVEL_DDD && gCurrLevelNum != LEVEL_THI) ||
    // Well, kick us from the wiggler room tho.
    (gCollectedStar == 5 && gCurrLevelNum == LEVEL_THI) ||
    // Let the bonus levels kick us out too
    (gCollectedStar == 0 && (gCurrLevelNum == LEVEL_PSS || gCurrLevelNum == LEVEL_COTMC || gCurrLevelNum == LEVEL_TOTWC ||
    gCurrLevelNum == LEVEL_VCUTM || gCurrLevelNum == LEVEL_WMOTR || gCurrLevelNum == LEVEL_SA))
    ))
        return FALSE;
    return gStayInLevel && gCurrLevelNum != LEVEL_BOWSER_1 && gCurrLevelNum != LEVEL_BOWSER_2 && gCurrLevelNum != LEVEL_BOWSER_3
    && gCurrLevelNum != LEVEL_CASTLE && gCurrLevelNum != LEVEL_CASTLE_COURTYARD && gCurrLevelNum != LEVEL_CASTLE_GROUNDS;
}

s8 restart_level_after_star() {
    return gRestartLevelAfterStar &&
    gCurrLevelNum != LEVEL_BOWSER_1 && gCurrLevelNum != LEVEL_BOWSER_2 && gCurrLevelNum != LEVEL_BOWSER_3 &&
    gCurrLevelNum != LEVEL_CASTLE && gCurrLevelNum != LEVEL_CASTLE_COURTYARD && gCurrLevelNum != LEVEL_CASTLE_GROUNDS &&
    gCurrLevelNum != LEVEL_BITDW && gCurrLevelNum != LEVEL_BITFS && gCurrLevelNum != LEVEL_BITS &&
    gCurrLevelNum != LEVEL_PSS && gCurrLevelNum != LEVEL_COTMC && gCurrLevelNum != LEVEL_TOTWC &&
    gCurrLevelNum != LEVEL_VCUTM && gCurrLevelNum != LEVEL_WMOTR && gCurrLevelNum != LEVEL_SA &&
    ((save_file_get_flags() & (SAVE_FLAG_HAVE_KEY_2 | SAVE_FLAG_UNLOCKED_UPSTAIRS_DOOR)) || gCurrLevelNum != LEVEL_DDD);
}