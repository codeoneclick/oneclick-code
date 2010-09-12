package  
{
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.events.TimerEvent;
	import flash.geom.Point;
	import flash.net.URLRequest;
	import flash.utils.Dictionary;
	import flash.utils.Timer;
	/**
	 * ...
	 * @author OneClick
	 */
	public class ContentLoader
	{
		private var m_Path:String;
		private var m_PNGLoaderList:Dictionary;
		private var m_PNGSizeScale:Point;
		
		private var m_LoadIndex:int;
		private var m_LoadTimer:Timer;
		
		public function ContentLoader(Path:String) 
		{
			m_Path = Path;
			m_PNGSizeScale = new Point(128, 128);
			m_PNGLoaderList = new Dictionary();
			
			m_LoadIndex = 0;
			m_LoadTimer = new Timer(300);
			m_LoadTimer.addEventListener(TimerEvent.TIMER, OnLoading);
		}
		
		public function Start():void
		{
			GameStates.m_State = GameStates.GAME_PRELOAD;
			m_LoadTimer.start();
		}
		
		public function LoadPNG(value:String):void
		{
			m_LoadIndex++;
			m_PNGLoaderList[value] = new Loader();
			m_PNGLoaderList[value].contentLoaderInfo.addEventListener(Event.COMPLETE, OnLoadPNG);
			m_PNGLoaderList[value].load(new URLRequest(m_Path + value + ".png"));
		}
		
		private function OnLoadPNG(event:Event):void
		{
			var URL:String = event.target.url;
			var value:String = URL.substring(m_Path.length + URL.search(m_Path), URL.length - 4);
			Resource.m_ContainerPNG[value] = new BitmapData(m_PNGSizeScale.x, m_PNGSizeScale.y, true, 0x00FFFFFF);
			(Resource.m_ContainerPNG[value] as BitmapData).draw(m_PNGLoaderList[value]); 
			m_LoadIndex--;
		}
		
		private function OnLoading(event:TimerEvent):void
		{
			if (m_LoadIndex == 0)
			{
				m_LoadTimer.reset();
				GameStates.m_State = GameStates.GAME_START;
			}
			
		}
		
	}

}