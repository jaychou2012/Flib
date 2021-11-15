package com.fl.flib;

public class Utils {

    public static final int MODE_NORMAL = 0;//正常
    public static final int MODE_FUNNY = 1;//搞笑
    public static final int MODE_UNCLE = 2;//大叔
    public static final int MODE_LOLITA = 3; //萝莉
    public static final int MODE_ROBOT = 4;//机器人
    public static final int MODE_ETHEREAL = 5;//空灵
    public static final int MODE_CHORUS = 6;//混合
    public static final int MODE_HORROR = 7;//恐怖

    // Used to load the 'flib' library on application startup.
    static {
        System.loadLibrary("libfmod");
        System.loadLibrary("libfmodL");
        System.loadLibrary("flib");
    }

    public static native  int playSound(String path, int type);

    public static native void stopPlay();

    public static native void resumePlay();

    public static native void pausePlay();

    public static native boolean isPlaying();

    public static native int saveSound(String path, int type, String savePath);

    public void saveSoundAsync(String path, int type, String savePath, ISaveSoundListener listener) {
        try {
            if (isPlaying()) {
                stopPlay();
            }
            int result = saveSound(path, type, savePath);
            if (result == 0) {
                listener.onFinish(path, savePath, type);
            } else {
                listener.onError("error");
            }
        } catch (Exception e) {
            listener.onError(e.getMessage());
        }
    }

    interface ISaveSoundListener {
        //成功
        public void onFinish(String path, String savePath, int type);

        //出错
        public void onError(String msg);
    }

}
