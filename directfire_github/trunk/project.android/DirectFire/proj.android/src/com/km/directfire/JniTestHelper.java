package com.km.directfire;

import android.os.Handler;
import android.os.Message;


public class JniTestHelper {
	
	private static Handler mHandler;
	private static String pname;
	
	public static void init(Handler handler)
	{
		JniTestHelper.mHandler = handler;
	}
	
    public static void setPackageName(String packageName)
    {
    	pname = packageName;
    }
    public static native void takePhotoFinish(int code);
    
    private static void takePhoto(final String title, final String text)
    {
    	Message msg = mHandler.obtainMessage();
    	msg.what = DirectFire.takephoto_start;
    	PramMessage dm = new PramMessage();
    	dm.title = title;
    	dm.msg = text;
    	msg.obj = dm;
    	msg.sendToTarget();
    }    
}

