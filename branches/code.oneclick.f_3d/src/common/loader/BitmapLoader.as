package common.loader 
{
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;
	import flash.utils.Dictionary;
	import game.Core;
	/**
	 * ...
	 * @author ...
	 */
	public class BitmapLoader 
	{
		private var m_requestList:Dictionary = new Dictionary();
		
		public function BitmapLoader() 
		{
			
		}
		
		public function Load(_name:String, _callback:Function):void
		{
			if (m_requestList[_name] != null)
			{
				(m_requestList[_name] as Requester).requesters.push(_callback);
			}
			else
			{
				var request:Requester = new Requester();
				request.requesters.push(_callback);
				m_requestList[_name] = request;
				
				request.loader = new Loader();
				request.loader.contentLoaderInfo.addEventListener(Event.COMPLETE, onLoadComplete);
				request.loader.load(new URLRequest(Core.k_CONTENT_PATH + _name + ".png"));
			}
		}
		
		private function onLoadComplete(_event:Event):void
		{
			var url:String = _event.target.url;
			var name:String = url.substring(Core.k_CONTENT_PATH.length + url.search(Core.k_CONTENT_PATH), url.length - ".png".length);
			
			if (m_requestList[name] != null)
			{
				for (var i:int = 0; i < (m_requestList[name] as Requester).requesters.length; i++)
				{
					((m_requestList[name] as Requester).requesters[i] as Function)(_event.target.content.bitmapData);
				}
				(m_requestList[name] as Requester).requesters = new Array();	
			}
		}
	}
}