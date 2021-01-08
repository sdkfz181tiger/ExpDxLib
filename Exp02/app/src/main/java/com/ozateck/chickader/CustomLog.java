package com.ozateck.chickader;

import android.content.Context;
import android.util.Log;
import android.widget.Toast;

/**
 * Created by ShimejiOzaki on 6/30/17.
 */

public class CustomLog {

	private static final boolean LOG_FLG = true;
	private static final boolean TOAST_FLG = true;

	public static void d(String tag, String text) {
		if (LOG_FLG) Log.d(tag, text);
	}

	public static void v(String tag, String text) {
		if (LOG_FLG) Log.v(tag, text);
	}

	public static void i(String tag, String text) {
		if (LOG_FLG) Log.i(tag, text);
	}

	public static void w(String tag, String text) {
		if (LOG_FLG) Log.w(tag, text);
	}

	public static void e(String tag, String text) {
		if (LOG_FLG) Log.e(tag, text);
	}

	public static void toast(Context context, String text) {
		if (TOAST_FLG) {
			Toast.makeText(context, text, Toast.LENGTH_SHORT).show();
		}
	}
}
