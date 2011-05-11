package game.enviroment 
{
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.events.MouseEvent;
	import flash.filters.GlowFilter;
	import flash.geom.ColorTransform;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	/**
	 * ...
	 * @author ...
	 */
	public class GroundCell extends GameNode
	{
		protected var m_intersect:Boolean = false;
		protected var m_levelEventCallback:Function = null;
		protected var m_isFilled:Boolean = false;
		
		public static const k_MOUSE_OVER:int = 1;
		public static const k_MOUSE_OUT:int = 2;
		public static const k_MOUSE_CLICK:int = 3;
		
		public static const k_WIDTH:int = 64;
		public static const k_HEIGHT:int = 64;
		
		public static const k_HIGHLIGHT_NONE:int = 1;
		public static const k_HIGHLIGHT_GREEN:int = 2;
		public static const k_HIGHLIGHT_RED:int = 3;
		
		protected var m_index:Point = new Point(0, 0);
		
		public function GroundCell(_container:DisplayObjectContainer, _size:Point, _index:Point, _resName:String, _eventCallback:Function) 
		{
			super(_container, _size, _resName);
			m_levelEventCallback = _eventCallback;
			m_index = _index;
		}
		
		public function set filled(_value:Boolean):void
		{
			m_isFilled = _value;
		}
		
		public function get filled():Boolean
		{
			return m_isFilled;
		}
		
		public function set index(_value:Point):void
		{
			m_index = _value;
		}
		
		public function get index():Point
		{
			return m_index;
		}
		
		override protected function onMouseOut(_event:MouseEvent):void 
		{
			super.onMouseOut(_event);
			m_intersect = false;
			m_levelEventCallback(this, k_MOUSE_OUT);
		}
		
		override protected function onMouseOver(_event:MouseEvent):void 
		{
			super.onMouseOver(_event);
			m_intersect = true;
			m_levelEventCallback(this, k_MOUSE_OVER);
		}
		
		override protected function update():void 
		{
			super.update();
			
			if (m_intersect)
			{
				filters = [ new GlowFilter(0xFFFFFF, 1, 4, 4,2,1,true) ];
			}
			else
			{
				filters = [];
			}
		}
		
		override protected function onResLoad(_data:BitmapData):void
		{
			m_texture.size = new Point(_data.width / Level.k_MAP_WIDTH, _data.height / Level.k_MAP_HEIGHT);
			m_bitamData = new BitmapData(_data.width / Level.k_MAP_WIDTH, _data.height / Level.k_MAP_HEIGHT);
			m_bitamData.copyPixels(_data, new Rectangle( m_index.x * m_bitamData.width, m_index.y * m_bitamData.height, m_bitamData.width, m_bitamData.height), new Point(0, 0));
			m_texture.bitmapData = m_bitamData;
		}
		
		public function highlight(_value:int):void
		{
			switch(_value)
			{
				case k_HIGHLIGHT_NONE :
				{
					transform.colorTransform = new ColorTransform( 1, 1, 1);
				}
				break;
				
				case k_HIGHLIGHT_GREEN :
				{
					transform.colorTransform = new ColorTransform( 0, 1, 0);
				}
				break;
				
				case k_HIGHLIGHT_RED :
				{
					transform.colorTransform = new ColorTransform( 1, 0, 0);
				}
				break;
			}
		}
		
	}

}