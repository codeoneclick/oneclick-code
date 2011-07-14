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
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class GameNode extends Sprite
	{
		protected var m_container:DisplayObjectContainer = null;
		protected var m_intersect:Boolean = false;
		protected var m_bitmap:Bitmap = null;
		protected var m_position:Point = new Point( 0, 0);
	
		public function GameNode(_container:DisplayObjectContainer) 
		{
			m_container = _container;
			m_bitmap = new Bitmap();
			this.addChild(m_bitmap);
			m_container.addChild(this);
			
			addEventListener(Event.ENTER_FRAME, onUpdate, false, 0, true);
			addEventListener(MouseEvent.MOUSE_OUT, onMouseOut, false, 0, true);
			addEventListener(MouseEvent.MOUSE_OVER, onMouseOver, false, 0, true);
			addEventListener(MouseEvent.MOUSE_DOWN, onMouseDown, false, 0, true);
		}
		
		public function Load(_name:String):void
		{
			Global.resourceController.LoadPNG(_name, onLoadResource);
		}
		
		protected function onLoadResource(_data:BitmapData):void
		{
			m_bitmap.bitmapData = _data;
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
			m_intersect = false;
		}
		
		protected function onMouseOver(_event:MouseEvent):void
		{
			m_intersect = true;
		}
		
		protected function onMouseDown(_event:MouseEvent):void
		{
			Load( "tile_0" + Global.editorController.previewSelectedIndex );
		}
		
		public function set position(_value:Point):void
		{
			m_position = _value;
		}
		
		public function get position():Point
		{
			return m_position;
		}
		
	}

}