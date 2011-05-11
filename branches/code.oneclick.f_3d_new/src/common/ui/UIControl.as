package common.ui 
{
	import flash.display.DisplayObject;
	import flash.display.DisplayObjectContainer;
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	/**
	 * ...
	 * @author ...
	 */
	public class UIControl 
	{
		public static const k_UI_RES_PATH:String = "Content/dev/ui/";
		
		protected var m_resName:String = "";
		protected var m_loader:Loader = null;
		protected var m_container:DisplayObjectContainer = null;
		protected var m_source:Object = null;
		private var m_initiator:Function = null;
		
		public function UIControl(_resName:String, _container:DisplayObjectContainer,_initiator:Function) 
		{
			m_resName = _resName;
			m_initiator = _initiator;
			m_container = _container;
			init();
		}
		
		private function init():void
		{
			m_loader = new Loader();
			m_loader.contentLoaderInfo.addEventListener(Event.INIT, onLoad);
			m_loader.load(new URLRequest(k_UI_RES_PATH + m_resName + ".swf"));	
		}
		
		private function onLoad(_event:Event):void
		{
			m_source = m_loader.content;
			m_loader.removeEventListener(Event.INIT, onLoad);
			m_initiator();
		}
		
	}

}