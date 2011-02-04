package 
{
	import flash.display.MovieClip;
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.KeyboardEvent;
	import flash.events.TimerEvent;
	import flash.utils.Timer;
	import Game.elements.TileController;
	import Game.level.LevelController;
	
	/**
	 * ...
	 * @author OneClick
	 */
	public class Main extends Sprite 
	{
		private var m_levelController:LevelController;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			m_levelController = new LevelController(this);	
		}	
	}
}