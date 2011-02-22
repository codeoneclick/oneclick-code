package 
{
	import common.helper3d.Sprite3d;
	import common.loader.ContentLoader;
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
	import game.Tile;


	public class  Main extends Sprite 
	{
		private var m_planes:Array = null;  			
		private var m_loader:ContentLoader = null; 	
		
		public static const k_MAP_WIDTH:int  = 12;
		public static const k_MAP_HEIGHT:int = 12;
		
		public static const k_TILE_WIDTH:int = 128;
		public static const k_TILE_HEIGHT:int = 128;
		
		private var m_mousePressed:Boolean = false;
		private var m_cameraOffset:Point = new Point();
		private var m_mouseOldPos:Point = new Point();
	
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
			
			m_loader = new ContentLoader(this);
			m_loader.Path = "Content/";
			m_loader.imagesPath = "Content/";
			m_loader.LoadImage("TreasureMap");	

			m_planes = new Array();
			for (var i:int = 0; i < k_MAP_WIDTH; i++)
			{
				m_planes[i] = new Array();
				for (var j:int = (k_MAP_HEIGHT - 1); j >= 0; j--)
				{
					m_planes[i][j] = new Tile(this, new Point(k_TILE_WIDTH, k_TILE_HEIGHT), "TreasureMap", new Point(i, j));
					m_planes[i][j].Rotation.x = 1.57;
					addChild(m_planes[i][j]);
				}
			}
			
			stage.addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
			stage.addEventListener(MouseEvent.MOUSE_UP, onMouseUp);
			stage.addEventListener(MouseEvent.MOUSE_MOVE, onMouseMove);
		}	
		
		private function onMouseDown(_event:MouseEvent):void
		{
			m_mousePressed = true;
		}
		
		private function onMouseUp(_event:MouseEvent):void
		{
			m_mousePressed = false;
		}
		
		private function onMouseMove(_event:MouseEvent):void
		{
			if (m_mousePressed)
			{
				var offsetX:int = m_mouseOldPos.x - _event.localX;
				var offsetY:int = m_mouseOldPos.y - _event.localY;
			
				if (offsetX != 0)
					m_cameraOffset.x -= offsetX;
				
				if (offsetY != 0)
					m_cameraOffset.y += offsetY;
			}
				
			m_mouseOldPos.x = _event.localX;
			m_mouseOldPos.y = _event.localY;
		}

		private function update(_event:Event):void
		{
			if (m_cameraOffset.y < 128 )
				m_cameraOffset.y = 128;
				
			if (m_cameraOffset.y > 768 )
				m_cameraOffset.y = 768;
				
			if (m_cameraOffset.x > 512)
				m_cameraOffset.x = 512;
				
			if (m_cameraOffset.x < -1024)
				m_cameraOffset.x = -1024;
			
			for (var i:int = 0; i < k_MAP_WIDTH; i++)
			{
				for (var j:int = 0; j < k_MAP_HEIGHT; j++)
				{
					m_planes[i][j].Position.y = -200;
					m_planes[i][j].Position.x = k_TILE_WIDTH / 2 * i + m_cameraOffset.x;
					m_planes[i][j].Position.z = k_TILE_HEIGHT / 2 * j + m_cameraOffset.y;
					//m_planes[i][j].update();
					//m_planes[i][j].rasterize();
				}
			}
		}
	}
}