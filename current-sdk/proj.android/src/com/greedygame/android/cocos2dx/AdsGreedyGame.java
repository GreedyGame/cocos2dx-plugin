package com.greedygame.android.cocos2dx;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.widget.FrameLayout;
import android.widget.Toast;

import com.greedygame.android.FloatAdLayout;
import com.greedygame.android.GreedyGameAgent;
import com.greedygame.android.GreedyGameAgent.FETCH_TYPE;
import com.greedygame.android.GreedyGameAgent.OnINIT_EVENT;
import com.greedygame.android.IAgentListner;


public class AdsGreedyGame  {

    private static Context mContext = null;
    protected static GLSurfaceView sGLSurfaceView = null; 
    protected static String TAG = "AdsGreedyGame";
    private static GreedyGameAgent ggAgent = null;
    private static FloatAdLayout floatAdLayout = null;
    
    
    public static native void onEvent(int d);

    public static native void onDownload(float p);
    
    public static void setup(Context context, GLSurfaceView value) {
    	try{
	    	if(!isEnable) {
	    		LogD("GreedyGame has been disabled manually!!");
	    		return;
	    		
	    	}
	    	LogD("GreedyGame is started!!");
	    	mContext = context;
	    	
	    	GreedyGameAgent.GameEngine="cocos2dx";
	        ggAgent = new GreedyGameAgent((Activity) mContext, new AdsGreedyGame.GreedyListner());        
	        sGLSurfaceView = value;
	        floatAdLayout = new FloatAdLayout(context);
	        ((Activity) mContext).runOnUiThread(
				new Runnable() {
					public void run() {
						FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(
								FrameLayout.LayoutParams.WRAP_CONTENT,
								FrameLayout.LayoutParams.WRAP_CONTENT);
						((Activity) mContext).addContentView(floatAdLayout, params);
					}
				});
    	}catch(Exception e){
    		LogE("Aporting this session", e);
    	}
    }
    
    static boolean isEnable = true;
    public static void setEnable(boolean s) {
    	isEnable = s;
    }
    
    private static List<String> units = null;
    public static void initialize() {
    	try{
	    	if(!isEnable) {
	    		LogD("GreedyGame has been disabled manually!!");
	    		return;
	    	}
	        units = new ArrayList<String>();
	        listAssetFiles("greedygame");
	        String[] unit_array = new String[units.size()];
	        units.toArray(unit_array);
	        ggAgent.init(unit_array, FETCH_TYPE.DOWNLOAD_BY_PATH);
	        
    	}catch(Exception e){
    		LogE("Aporting this session", e);
    	}
    }
    
    public static String getActivePath() {
    	try{
        	if(!isEnable) {
        		LogD("GreedyGame has been disabled manually!!");
        		return null;
        	}
    		return ggAgent.getActivePath();
    	}catch(Exception e){
			LogE("Aporting this session", e);
			return null;
		}
    }
  
    
    public static void fetchAdHead(String unit_id) {
    	try{
	    	if(!isEnable) {
	    		LogD("GreedyGame has been disabled manually!!");
	    		return;
	    	}
	    	floatAdLayout.fetchHeadAd(unit_id);
    	}catch(Exception e){
			LogE("Aporting this session", e);
			return;
		}    	
    }
    
    public static void fetchAdHead(String unit_id, int x, int y) {
    	try{
	    	if(!isEnable) {
	    		LogD("GreedyGame has been disabled manually!!");
	    		return;
	    	}
	    	floatAdLayout.fetchHeadAd(unit_id, x, y);
	    	
    	}catch(Exception e){
			LogE("Aporting this session", e);
			return;
		}    	
    }
    
    public static void removeAdHead() {
    	try{
	    	if(!isEnable) {
	    		LogD("GreedyGame has been disabled manually!!");
	    		return;
	    	}
	    	
	    	((Activity) mContext).runOnUiThread(
					new Runnable() {
						public void run() {
							floatAdLayout.removeAllHeadAd();
						}
					});
    	}catch(Exception e){
			LogE("Aporting this session", e);
			return;
		}    	
    }
    
    private static boolean isDebug = true;
    public static void setDebug(boolean b){
    	
    	try{
	    	if(!isEnable) {
	    		LogD("GreedyGame has been disabled manually!!");
	    		return;
	    	}
	    	isDebug = b;
	    	ggAgent.setDebug(b);
    	}catch(Exception e){
			LogE("Aporting this session", e);
		}
    }
    
    
    private static void LogE(String msg, Exception e) {
        Log.e(TAG, msg, e);
        e.printStackTrace();
        
        //Start without campaign
        isEnable = false;
        _onEventInThread(-1);
    }

    
    private static void LogD(String msg) {
     
            Log.d(TAG, msg);
        
    }
    
    
    private static void runOnGLThread(Runnable r) {
		if (null != sGLSurfaceView) {
			sGLSurfaceView.queueEvent(r);
		} else {
			LogD("runOnGLThread sGLSurfaceView is null");
			r.run();
		}
	}
    
	public static void onResume(){
		if(ggAgent != null) {
	    	ggAgent.onResume();
    	}		
	}
	
	public static void onPause(){
		if(ggAgent != null) {
	    	ggAgent.onPause();
    	}
	}
	
	public static void onResume(String name){
		if(ggAgent != null) {
	    	ggAgent.onResume(name);
    	}		
	}
	
	public static void onPause(String name){
		if(ggAgent != null) {
	    	ggAgent.onPause(name);
    	}
	}
	
	
	
	
    public static void onCustomEvent(String eventName){
    	if(ggAgent != null){
    		ggAgent.onCustomEvent(eventName);
    	}
    }
    
    private static class GreedyListner implements IAgentListner{

		@Override
		public void onProgress(float progress){
			LogD("progress "+(progress)+"%");
			_onDownloadInThread(progress);
			}

		@Override
		public void onDownload(boolean success) {
			_onEventInThread(2);
		}

		@Override
		public void onInit(OnINIT_EVENT arg) {
			
			
			/*
			 * -1 = using no campaign
			 * 0 = campaign already cached
			 * 1 = new campaign found to download
			 * 2 = new campaign is downloaded
			 */     
			int r = -1;
			if(OnINIT_EVENT.CAMPAIGN_NOT_AVAILABLE == arg){
				r = -1;
			}else if(OnINIT_EVENT.CAMPAIGN_CACHED == arg){
				r = 0;
			}else if(OnINIT_EVENT.CAMPAIGN_FOUND == arg){
				r = 1;
			}
			
   			_onEventInThread(r);
		}

		@Override
		public void unAvailablePermissions(ArrayList<String> arg0) {
			
		
			
		}

    }
    
    private static boolean listAssetFiles(String path) {
    	if(!isEnable) {
    		return false;
    	}
        String [] list;
        try {
            list = mContext.getAssets().list(path);
            if (list.length > 0) {
                // This is a folder
                for (String file : list) {
                    if (!listAssetFiles(path + "/" + file))
                        return false;
                }
            } else {
                // This is a file
            	//greedygame/
            	if(path.startsWith("greedygame") && path.length() > 11){
	            	String p = path.substring(11);
	            	units.add(p);
            	}
            }
        } catch (IOException e) {
            return false;
        }
        return true; 
    } 

    private static void _onEventInThread(final int d) {
		runOnGLThread(new Runnable(){
			@Override
			public void run() {
				onEvent(d);
			}
		});
	}
    
    private static void _onDownloadInThread(final float d) {
		runOnGLThread(new Runnable(){
			@Override
			public void run() {
				onDownload(d);
			}
		});
	}
    
}

  
