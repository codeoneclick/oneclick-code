package 
{
	import flash.display.Sprite;
	import flash.events.Event;
	import ui.UILoginWindowController;
	import ui.UILoginWindowView;
	
	/**
	 * ...
	 * @author sergey.sergeev.code.oneclick
	 */
	public class Main extends Sprite 
	{
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			
			var loginMenu:UILoginWindowController = new UILoginWindowController(this, new UILoginWindowView());
		}
		
	}
	
}