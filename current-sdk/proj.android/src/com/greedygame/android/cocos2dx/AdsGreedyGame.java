package com.greedygame.android.cocos2dx;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import com.greedygame.android.adhead.FloatAdLayout;
import com.greedygame.android.agent.GreedyGameAgent;
import com.greedygame.android.agent.GreedyGameAgent.FetchType;
import com.greedygame.android.agent.GreedyGameAgent.OnInitEvent;
import com.greedygame.android.agent.IAgentListener;

import android.app.Activity;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;
import android.widget.FrameLayout;
import android.widget.Toast;




public class AdsGreedyGame  {

    private static Context mContext = null;
    protected static GLSurfaceView sGLSurfaceView = null; 
    protected static String TAG = "AdsGreedyGame";
    private static GreedyGameAgent ggAgent = null;
    private static FloatAdLayout floatAdLayout = null;
    
    
    public static native void onEvent(int d);

    public static native void onDownload(float p);
    
    private static final ArrayList<String> floatUnits = new ArrayList<String>();
    private static final ArrayList<String> nativeUnits = new ArrayList<String>();
    
    private static boolean isDebug = false;
    
    
    // Add the float-unit-ids used in your game here
    public static void addFloatUnits(String unitId) {
    	//floatUnits.add("your-float-unit-id");
		floatUnits.add(unitId);
		
	}
    
    public static void addNativeUnits(String unitId) {
    	nativeUnits.add(unitId);
    }
    
    
    public static void setup(Activity activity, GLSurfaceView value) {
    	
    	
    	try{
	    	if(!isEnable) {
	    		LogD("GreedyGame has been disabled manually!!");
	    		return;
	    		
	    	}
	    	LogD("GreedyGame is started!!");
	    	mContext = activity;
	    	
	    	
	        ggAgent = GreedyGameAgent.install((Activity) mContext, new AdsGreedyGame.GreedyListener());     
	        ggAgent.gameEngine="cocos2dx";
	        sGLSurfaceView = value;
	        floatAdLayout = new FloatAdLayout((Activity) mContext);
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
	    	units.addAll(floatUnits);
	    	units.addAll(nativeUnits);
	    	String [] unit_array = new String[units.size()];
	    	units.toArray(unit_array);
	    	
	        ggAgent.init(unit_array, FetchType.DOWNLOAD_BY_PATH);
	        ggAgent.setDebugLog(true);
	        LogD("initialized with size "+units.size());
	        
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
  
    
    public static void fetchAdHead(final String unit_id) {
    	try{
	    	if(!isEnable) {
	    		LogD("GreedyGame has been disabled manually!!");
	    		return;
	    	}
	    	((Activity) mContext).runOnUiThread(
					new Runnable() {
						public void run() {
							floatAdLayout.fetchHeadAd(unit_id);
						}
					});
	    	
    	}catch(Exception e){
			LogE("Aporting this session", e);
			return;
		}    	
    }
    
    
    
    public static void showEngagementWindow(String unitId) {
    	floatAdLayout.showEngagementWindow(unitId);
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
							floatAdLayout.remove();
						}
					});
    	}catch(Exception e){
			LogE("Aporting this session", e);
			return;
		}    	
    }
    
    
    public static void setDebug(boolean b){
    	
    	try{
	    	if(!isEnable) {
	    		LogD("GreedyGame has been disabled manually!!");
	    		return;
	    	}
	    	isDebug = b;
	    	ggAgent.setDebugCampaign(b);
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
   
    
    private static class GreedyListener implements IAgentListener{


		@Override
		public void onInit(OnInitEvent arg) {
			
			
			/*
			 * -1 = campaign not available
			 * 1 = new campaign found to download
			 */     
			int r = -1;
			if(OnInitEvent.CAMPAIGN_NOT_AVAILABLE == arg){
				r = -1;
			}else if(OnInitEvent.CAMPAIGN_AVAILABLE == arg){
				r = 1;
			}
			
   			_onEventInThread(r);
		}


		@Override
		public void onDownload() {
			// TODO Auto-generated method stub
			_onEventInThread(2);
		}

		@Override
		public void onError() {
			// TODO Auto-generated method stub
			_onEventInThread(-1);
		}

		@Override
		public void onProgress(float arg0) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onPermissionsUnavailable(ArrayList<String> arg0) {
			// TODO Auto-generated method stub
			
		}

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

  
