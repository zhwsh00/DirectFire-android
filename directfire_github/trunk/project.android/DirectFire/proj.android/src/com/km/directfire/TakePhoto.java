package com.km.directfire;
import android.app.Activity;
import android.content.ContentResolver;
import android.net.Uri;
import android.graphics.Bitmap;    
import android.graphics.Bitmap.CompressFormat;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.provider.MediaStore;
import android.util.*;
import java.io.File;  
import java.io.FileNotFoundException;
import java.io.FileOutputStream;  
import java.io.IOException;
import java.io.InputStream; 

public class TakePhoto extends Activity {
	public static String pngPath;
	public static final int CANCEL_CODE = 1;
	public static final int ALBUM_CODE = 2;
	public static final int CAMERA_CODE = 3;
	public static final int PHOTO_SUCCESS = 4;
	public static final int PHOTO_FAILED = 5;
	private Button cancelButton = null;
	private Button albumButton = null;
	private Button cameraButton = null;
	public static void setPngPath(String path){
		pngPath = path;
	}
	@Override
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		
		setContentView(R.layout.takephoto);
		cancelButton = (Button)findViewById(R.id.cancel);
		//albumButton = (Button)findViewById(R.id.album);
		cameraButton = (Button)findViewById(R.id.camera);
		
		cancelButton.setOnClickListener(cancellistener);
		//albumButton.setOnClickListener(albumlistener);
		cameraButton.setOnClickListener(cameralistener);
	}
	private OnClickListener cancellistener = new OnClickListener() {
		
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			Intent intent = new Intent();
			setResult(CANCEL_CODE,intent);
			finish();
		}
	}
	;private OnClickListener albumlistener = new OnClickListener() {
		
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			Intent albmuIntent = new Intent(Intent.ACTION_GET_CONTENT); 
			albmuIntent.setType("image/*");  
			startActivityForResult(albmuIntent, 30);
		}
	};
	private OnClickListener cameralistener = new OnClickListener() {
		
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			Intent cameraIntent = new Intent(android.provider.MediaStore.ACTION_IMAGE_CAPTURE); 
			startActivityForResult(cameraIntent, 31);
		}
	};
	@Override
	protected void onActivityResult(int requestCode,int resultCode,Intent data){
		super.onActivityResult(requestCode, resultCode, data);
		if(requestCode == 31){
			if(resultCode == RESULT_OK){
				Bitmap original = (Bitmap)data.getExtras().get("data");
				FileOutputStream stream;
				try {
					stream = new FileOutputStream(pngPath);
				} catch (FileNotFoundException e1) {
					//return failed
					Intent intent = new Intent();
					setResult(PHOTO_FAILED,intent);
					finish();
					return;
				}
				original.compress(CompressFormat.PNG, 80, stream);
				original.recycle();
				try {
					stream.close();
				} catch (IOException e) {
					//return failed
					Intent intent = new Intent();
					setResult(PHOTO_FAILED,intent);
					finish();
					return;
				}
				Intent intent = new Intent();
				setResult(PHOTO_SUCCESS,intent);
				finish();
				return;
			}else{
				//canceled
				Intent intent = new Intent();
				setResult(CANCEL_CODE,intent);
				finish();
			}
		}else if(requestCode == 30){
			if(resultCode == RESULT_OK){
				ContentResolver resolver = getContentResolver();
                Uri originalUri = data.getData();
                try {
                    Bitmap original = MediaStore.Images.Media.getBitmap(resolver, originalUri);  
                    if (original != null) {
        				FileOutputStream stream;
        				try {
        					stream = new FileOutputStream(pngPath);
        				} catch (FileNotFoundException e1) {
        					//return failed
        					Intent intent = new Intent();
        					setResult(PHOTO_FAILED,intent);
        					finish();
        					return;
        				}
        				Boolean ok = original.compress(CompressFormat.PNG, 80, stream);
        				original.recycle();
        				try {
        					stream.close();
        				} catch (IOException e) {
        					//return failed
        					Intent intent = new Intent();
        					setResult(PHOTO_FAILED,intent);
        					finish();
        					return;
        				}
        				Intent intent = new Intent();
        				if(ok)
        					setResult(PHOTO_SUCCESS,intent);
        				else
        					setResult(PHOTO_FAILED,intent);
        				finish();
        				return;
                    } 
                } catch (FileNotFoundException e) {  
					Intent intent = new Intent();
					setResult(PHOTO_FAILED,intent);
					finish();
					return; 
                } catch (IOException e) {  
					Intent intent = new Intent();
					setResult(PHOTO_FAILED,intent);
					finish();
					return; 
                }
			}else{
				//canceled
				Intent intent = new Intent();
				setResult(CANCEL_CODE,intent);
				finish();
			}
		}
	};
}
