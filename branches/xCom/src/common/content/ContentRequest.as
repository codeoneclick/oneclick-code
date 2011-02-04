package common.content 
{
	import flash.display.Loader;
	/**
	 * ...
	 * @author ...
	 */
	public class ContentRequest
	{
		private var m_requesterList:Array = null;
		private var m_loader:Loader = null;
		public function ContentRequest()
		{
			m_requesterList = new Array();
		}
		
		public function get requester():Array
		{
			return m_requesterList;
		}
		
		public function set requester(_value:Array):void
		{
			m_requesterList = _value;
		}
		
		public function get loader():Loader
		{
			return m_loader;
		}
		
		public function set loader(_value:Loader):void
		{
			m_loader = _value;
		}
	}

}