package com.ozateck.chickader;

import android.content.Context;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;
import okhttp3.ResponseBody;

public class HttpConnector implements HttpTask.HttpEventListener {

	private static final String TAG = "HttpConnector";
	private Context ctx;

	HttpConnector(final Context ctx) {
		CustomLog.d(TAG, "HttpConnector");
		this.ctx = ctx;
	}

	void connect(final String url, final String fileName) {
		CustomLog.d(TAG, "connect()");
		// HttpTask
		HttpTask task = new HttpTask(ctx, url, fileName, this);
		// Execute
		ExecutorService eService = Executors.newSingleThreadExecutor();
		eService.execute(task);
	}

	@Override
	public void onSuccess(final String fileName) {
		CustomLog.d(TAG, "onSuccess()");
		MainActivity.nativeOnHttpSuccess(fileName);// JNI
	}

	@Override
	public void onProgress(final String fileName) {
		CustomLog.d(TAG, "onProgress():" + fileName);
		MainActivity.nativeOnHttpProgress(fileName);// JNI
	}

	@Override
	public void onError(final String fileName, final String err) {
		CustomLog.d(TAG, "onError()");
		MainActivity.nativeOnHttpError(fileName, err);// JNI
	}
}

class HttpTask implements Runnable {

	private static final String TAG = "HttpTask";
	private Context ctx = null;
	private String url = null;
	private String fileName = null;
	private HttpEventListener listener = null;

	HttpTask(final Context ctx, final String url,
	         final String fileName, HttpEventListener listener) {
		CustomLog.d(TAG, "HttpTask");
		this.ctx = ctx;
		this.url = url;
		this.fileName = fileName;
		this.listener = listener;
	}

	@Override
	public void run() {
		CustomLog.d(TAG, "run()");
		final OkHttpClient client = new OkHttpClient();
		final Request req = new Request.Builder().url(url+fileName).build();
		try {
			Response res = client.newCall(req).execute();
			if (res.isSuccessful()) executeStreams(res.body());
			if (listener != null) listener.onSuccess(fileName);// Success
		} catch (IOException e) {
			if (listener != null) listener.onError(fileName, e.toString());// Error
		}
	}

	private void executeStreams(final ResponseBody body) throws IOException {
		// InputStream, OutputStream
		InputStream iStream = body.byteStream();
		OutputStream oStream = ctx.openFileOutput(fileName, ctx.MODE_PRIVATE);
		int lenLoaded = 0, lenRead = 0;
		byte buffer[] = new byte[1024];
		while (0 < (lenRead = iStream.read(buffer, 0, buffer.length))) {
			lenLoaded += lenRead;
			oStream.write(buffer, 0, lenRead);
			if (listener != null) listener.onProgress(fileName);// Progress
		}
		oStream.flush();
		oStream.close();
		iStream.close();
	}

	interface HttpEventListener {

		void onSuccess(final String fileName);

		void onProgress(final String fileName);

		void onError(final String fileName, final String err);
	}
}