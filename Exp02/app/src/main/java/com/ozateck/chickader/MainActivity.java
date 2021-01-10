package com.ozateck.chickader;

import android.app.NativeActivity;
import android.content.Context;
import android.os.Bundle;

public class MainActivity extends NativeActivity{

	public static final String TAG = "MainActivity";
	public static String filePath = "";

	// Used to load the 'native-lib' library on application startup.
	static{
		System.loadLibrary("native-lib");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		MainActivity.nativeOnCreate();// Native

		// File path
		final Context ctx = this.getApplicationContext();
		filePath = ctx.getFilesDir().getPath();
	}

	@Override
	protected void onStart(){
		super.onStart();
		MainActivity.nativeOnStart();// Native
	}

	@Override
	protected void onResume(){
		super.onResume();
		MainActivity.nativeOnResume();// Native
	}

	@Override
	protected void onPause(){
		MainActivity.nativeOnPause();// Native
		super.onPause();
	}

	@Override
	protected void onStop(){
		MainActivity.nativeOnStop();// Native
		super.onStop();
	}

	@Override
	protected void onDestroy(){
		MainActivity.nativeOnDestroy();// Native
		super.onDestroy();
	}

	//==========
	// JNI(Java -> C++)
	public static native void nativeOnCreate();

	public static native void nativeOnStart();

	public static native void nativeOnResume();

	public static native void nativeOnPause();

	public static native void nativeOnStop();

	public static native void nativeOnDestroy();

	//==========
	// JNI(C++ -> Java)
	public static void sayHello(){
		CustomLog.d(TAG, "Say hello from C++!!");
	}

	public static void sayGood(){
		CustomLog.d(TAG, "Say good from C++!!");
	}

	public static void sayNice(){
		CustomLog.d(TAG, "Say nice from C++!!");
	}

	public static String sayYahoo(){
		CustomLog.d(TAG, "Say yahoo from C++!!");
		return "Bye bye Proguard!!";
	}
}