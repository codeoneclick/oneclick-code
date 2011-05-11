package common.loader 
{
	import flash.display.Loader;
	/**
	 * ...
	 * @author ...
	 */
	public class Requester 
	{
		private var m_loader:Loader = null;
		private var m_requesters:Array = new Array();
		
		public function set loader(_value:Loader):void
		{
			m_loader = _value;
		}
		
		public function get loader():Loader
		{
			return m_loader;
		}
		
		public function get requesters():Array
		{
			return m_requesters;
		}
		
		public function set requesters(_value:Array):void
		{
			m_requesters = _value;
		}
		
		public function Requester() 
		{
			
		}
		
	}

}