package 
{
	import common.helper3d.Sprite3d;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.events.TextEvent;
	import flash.events.TimerEvent;
	import flash.geom.Rectangle;
	import flash.utils.Timer;
	import flash.geom.Point;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.display.BitmapData;
	import flash.display.MovieClip;
	import flash.system.Capabilities;
	import flash.display.StageScaleMode;
	import game.core.Core;
	import game.Game;


	public class  Main extends Sprite 
	{	
		
		private var m_game:Game = null;
		
		public function Main():void 
		{
			if (stage) init();
			else addEventListener(Event.ADDED_TO_STAGE, init);
		}
		
		private function init(e:Event = null):void 
		{
			removeEventListener(Event.ADDED_TO_STAGE, init);
			stage.frameRate = 60;
			stage.scaleMode = StageScaleMode.NO_SCALE;
			stage.stageWidth = 100;
			
			Core.stage = stage;
			Core.displayContainer = this;
			Core.init();
			
			m_game = new Game();
		}	
	}
}