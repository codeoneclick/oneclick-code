package 
{
	import core.Global;
	import core.Input;
	import flash.display.Sprite;
	import flash.events.Event;
	import core.Camera;
	import game.SceneController;
	
	/**
	 * ...
	 * @author codeoneclick
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
			Global.stage = stage;
			Global.stage.frameRate = 60;
			Global.input = new Input();
			Global.camera = new Camera();
			Global.displayContainer = this;
			Global.sceneController = new SceneController();
		}
		
	}
	
}