package game 
{
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObject;
	import flash.display.DisplayObjectContainer;
	import flash.display.Sprite;
	import flash.events.Event;
	import core.Global;
	import flash.events.MouseEvent;
	import flash.filters.GlowFilter;
	import flash.geom.ColorTransform;
	import flash.geom.Point;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class GameNode extends Sprite
	{
		protected var m_container:DisplayObjectContainer = null;
		protected var m_intersect:uint = 0x00000000;
		protected var m_position:Point = new Point( 0, 0 );
	
		public function GameNode(_container:DisplayObjectContainer) 
		{
			m_container = _container;

			m_container.addChild(this);
			
			Global.inGameContainer.addEventListener( MouseEvent.CLICK, onMouseClick );
			
			addEventListener(Event.ENTER_FRAME, onUpdate, false, 0, true);
			addEventListener(MouseEvent.MOUSE_OUT, onMouseOut, false, 0, true);
			addEventListener(MouseEvent.MOUSE_OVER, onMouseOver, false, 0, true);
			addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown, false, 0, true);
		}
		
		public function Load(_name:String, _sectorType:String):void
		{
			Global.resourceController.LoadPNG(_name, onLoadResource);
		}
		
		public function LoadBoundData(_name:String):void
		{
			Global.resourceController.LoadPNG(_name, onLoadBoundData);
		}
		
		
		public function unLoadAll():void
		{
			m_container.removeChild(this);
			
			Global.inGameContainer.removeEventListener( MouseEvent.CLICK, onMouseClick );
			
			removeEventListener(Event.ENTER_FRAME, onUpdate);
			removeEventListener(MouseEvent.MOUSE_OUT, onMouseOut);
			removeEventListener(MouseEvent.MOUSE_OVER, onMouseOver);
			removeEventListener(MouseEvent.MOUSE_DOWN, onMouseDown);
		}
		
		protected function onLoadResource(_data:BitmapData):void
		{
			
		}
		
		protected function onLoadBoundData(_data:BitmapData):void
		{
			
		}
		
		protected function onUpdate(_event:Event):void
		{
			onIntersectUpdate();
			
			x = m_position.x - Global.camera.position.x;
			y = m_position.y - Global.camera.position.y;
		}
		
		protected function onIntersectUpdate():void
		{
			if (m_intersect)
			{
				transform.colorTransform = new ColorTransform(255, 1, 1);
			}
			else
			{
				transform.colorTransform = new ColorTransform(1, 1, 1);
			}
		}
		
		protected function onMouseOut(_event:MouseEvent):void
		{
			
		}
		
		protected function onMouseOver(_event:MouseEvent):void
		{

		}
		
		protected function onMouseDown(_event:MouseEvent):void
		{
			
		}
		
		protected function onMouseClick(_event:MouseEvent):void
		{
			
		}
		
		public function set position(_value:Point):void
		{
			m_position = _value;
		}
		
		public function get position():Point
		{
			return m_position;
		}
		
		public static function sorter(_value_01:GameNode, _value_02:GameNode):int
		{
			if (_value_01.position.y < _value_02.position.y)
				return -1;
			if (_value_01.position.y > _value_02.position.y)
				return 1;
			return 0;
		}
		
	}

}