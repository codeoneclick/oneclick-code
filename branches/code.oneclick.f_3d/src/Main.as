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
	import game.Camera;
	import game.Core;
	import game.Tile;


	public class  Main extends Sprite 
	{
		private var m_planes:Array = null;  			
		
		public static const k_MAP_WIDTH:int  = 12;
		public static const k_MAP_HEIGHT:int = 12;
		
		public static const k_TILE_WIDTH:int = 128;
		public static const k_TILE_HEIGHT:int = 128;
	
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
			stage.addEventListener(Event.ENTER_FRAME, update);
			
			Core.stage = stage;
			Core.init();

			m_planes = new Array();
			for (var i:int = 0; i < k_MAP_WIDTH; i++)
			{
				m_planes[i] = new Array();
				for (var j:int = (k_MAP_HEIGHT - 1); j >= 0; j--)
				{
					m_planes[i][j] = new Tile(this, new Point(k_TILE_WIDTH, k_TILE_HEIGHT), "TreasureMap", new Point(i, j));
					m_planes[i][j].Rotation.x = 1.57;
				}
			}
		}	
		
		private function update(_event:Event):void
		{
			for (var i:int = 0; i < k_MAP_WIDTH; i++)
			{
				for (var j:int = 0; j < k_MAP_HEIGHT; j++)
				{
					m_planes[i][j].Position.y = -200;
					m_planes[i][j].Position.x = k_TILE_WIDTH / 2 * i + Core.camera.Position.x;
					m_planes[i][j].Position.z = k_TILE_HEIGHT / 2 * j + Core.camera.Position.z;
				}
			}
		}
	}
}