/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.km.directfire;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;


import android.content.Intent;
import android.view.Menu;
import android.widget.Toast;
import android.os.*;
import android.util.*;

public class DirectFire extends Cocos2dxActivity{	
	public static final int takephoto_start = 0x0001;
	public static final int takephoto_cancel = 0x0002;
	public static final int takephoto_album = 0x0003;
	public static final int takephoto_camera = 0x0004;
	private static final int REQUEST_CODE=1;
	
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		JniTestHelper.init(mHandler);
		JniTestHelper.setPackageName(this.getPackageName());
	}
	
    static {
    	 System.loadLibrary("ev");
    	 System.loadLibrary("msgpack");
         System.loadLibrary("game");
    }
    public void takePhoto(String str)
    {
    	Log.e("takePhoto", str);
    	/*
    	Intent cameraIntent = new Intent(android.provider.MediaStore.ACTION_IMAGE_CAPTURE); 
    	startActivityForResult(cameraIntent, 31);
    	*/
    	
		Intent intent = new Intent();
		intent.setClass(DirectFire.this,TakePhoto.class);
		intent.putExtra("str","come from first activity");
		startActivityForResult(intent, REQUEST_CODE);		
    }
    
    private Handler mHandler = new Handler()
    {
		@Override
		public void handleMessage(Message msg) {
			switch(msg.what)
			{
			case takephoto_start:
				PramMessage pram = (PramMessage)msg.obj;
				TakePhoto.setPngPath(pram.msg);
				Intent intent = new Intent();
				intent.setClass(DirectFire.this,TakePhoto.class);
				intent.putExtra("str","come from first activity");
				startActivityForResult(intent, REQUEST_CODE);
				break;
			}
		}
    };
	@Override
	protected void onActivityResult(int requestCode,int resultCode,Intent data){
		super.onActivityResult(requestCode, resultCode, data);
		if(requestCode == REQUEST_CODE){
			if(resultCode == TakePhoto.CANCEL_CODE){
				JniTestHelper.takePhotoFinish(0);
			}else if(resultCode == TakePhoto.PHOTO_SUCCESS){
				JniTestHelper.takePhotoFinish(1);
			}else if(resultCode == TakePhoto.PHOTO_FAILED){
				JniTestHelper.takePhotoFinish(-1);
			}
		}
	};
}
