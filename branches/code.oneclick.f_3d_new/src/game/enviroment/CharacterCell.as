package game.enviroment 
{
	import flash.display.DisplayObjectContainer;
	import flash.events.MouseEvent;
	import flash.filters.GlowFilter;
	import flash.geom.ColorTransform;
	import flash.geom.Point;
	/**
	 * ...
	 * @author ...
	 */
	public class CharacterCell extends GameNode
	{
		protected var m_intersect:Boolean = false;
		protected var m_levelEventCallback:Function = null;
		
		public static const k_MOUSE_OVER:int = 1;
		public static const k_MOUSE_OUT:int = 2;
		public static const k_MOUSE_CLICK:int = 3;
		
		public static const k_HIGHLIGHT_NONE:int = 1;
		public static const k_HIGHLIGHT_GREEN:int = 2;
		public static const k_HIGHLIGHT_RED:int = 3;
		
		protected var m_isIntersected:Boolean = true;
		
		public function set isIntersected(_value:Boolean):void
		{
			m_isIntersected = _value;
			mouseEnabled = _value;
		}
		
		public function CharacterCell(_container:DisplayObjectContainer, _size:Point, _resName:String, _eventCallback:Function) 
		{
			super(_container, _size, _resName);
			m_levelEventCallback = _eventCallback;
		}
		
		override protected function onMouseOut(_event:MouseEvent):void 
		{
			if (m_isIntersected)
			{
				super.onMouseOut(_event);
				m_intersect = false;
				m_levelEventCallback(this, k_MOUSE_OUT);
			}
		}
		
		override protected function onMouseOver(_event:MouseEvent):void 
		{
			if (m_isIntersected)
			{
				super.onMouseOver(_event);
				m_intersect = true;
				m_levelEventCallback(this, k_MOUSE_OVER);
			}
		}
		
		override protected function update():void 
		{
			super.update();
			
			if (m_intersect)
			{
				filters = [ new GlowFilter(0xFFFFFF, 1, 4, 4) ];
			}
			else
			{
				filters = [];
			}
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