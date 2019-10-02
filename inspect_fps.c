#define FPS_AVERAGE 0
#define FPS_RANGE 1
#define FPS_BOTH 2

struct fpsStruct
{
    unsigned long startTime;

    stTime fpsTime;
    unsigned long fpsLastUpdate;

    int fpsHeap;
    int fpsCount;
    int fpsFindLowest;
    int fpsFindHighest;

    int fpsLowest;
    int fpsHighest;
    double fpsAverage;
}fpsController;

void fpsPrint(int mode);
void fpsUpdate(void);

void fpsPrint(int mode)
{
    fpsUpdate();

    switch (mode)
    {
        default:
        case FPS_AVERAGE:
            sprintf(text, "Avg. fps: %.02f", fpsController.fpsAverage);
        break;

        case FPS_RANGE:
            sprintf(text, "Min fps: %i\nMax fps: %i",
                fpsController.fpsLowest, fpsController.fpsHighest);
        break;

        case FPS_BOTH:
            sprintf(text, "Avg. fps: %.02f\nMin fps: %i\nMax fps: %i",
                fpsController.fpsAverage, fpsController.fpsLowest, fpsController.fpsHighest);
        break;
    }
}

void fpsUpdate(void)
{
    fpsController.fpsTime = getTime();

    if (!fpsController.fpsLastUpdate)
        fpsController.fpsLastUpdate = fpsController.fpsTime.sec_utc;

    if (!fpsController.fpsCount)
    {
        fpsController.fpsFindLowest = 512;
        fpsController.fpsFindHighest = 0;
    }

    fpsController.fpsHeap += real_fps;
    fpsController.fpsCount ++;

    if (real_fps < fpsController.fpsFindLowest) fpsController.fpsFindLowest = real_fps;
    if (real_fps > fpsController.fpsFindHighest) fpsController.fpsFindHighest = real_fps;

    if (fpsController.fpsTime.sec_utc != fpsController.fpsLastUpdate)
    {
        fpsController.fpsAverage = fpsController.fpsHeap / (double) fpsController.fpsCount;
        fpsController.fpsLowest = fpsController.fpsFindLowest;
        fpsController.fpsHighest = fpsController.fpsFindHighest;
        fpsController.fpsHeap = 0;
        fpsController.fpsCount = 0;
        fpsController.fpsFindLowest = 512;
        fpsController.fpsFindHighest = 0;

        fpsController.fpsLastUpdate = fpsController.fpsTime.sec_utc;
    }
}
