package Digger 
{
	import flash.events.KeyboardEvent;
	/**
	 * ...
	 * @author OneClick
	 */
	public class Input
	{
		public static var m_KeyboardCodes:Array;
		
		public function Input() 
		{
			m_KeyboardCodes = new Array();
		}
		
		public function OnKeyDown(event:KeyboardEvent):void
		{
			event.updateAfterEvent();
			m_KeyboardCodes[event.keyCode] = true;
		}

		public function OnKeyUp(event:KeyboardEvent):void
		{
			m_KeyboardCodes[event.keyCode] = false;
		}
		
	}

}