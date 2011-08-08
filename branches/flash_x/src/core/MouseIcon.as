package core
{	
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.MouseEvent;
	import flash.geom.Point;
	
	import mx.core.Application;

	public class MouseIcon
	{
		public static const k_MOUSE_ICON_NAME:String = "MouseIcon";
		public static const k_DEFAULT_OFFSET_X:int = 0;
		public static const k_DEFAULT_OFFSET_Y:int = 0;
		
		public const name:String = "MouseIcon";

		private var m_sprite:Sprite;		
		private var m_staticIcon:Sprite;
		private var m_container:DisplayObjectContainer;
		private var m_loadedIcon:Bitmap;
		
		// Offsets
		private var m_offsetX:int = k_DEFAULT_OFFSET_X;
		private var m_offsetY:int = k_DEFAULT_OFFSET_Y;
		
		private static var s_point:Point;				
		
		public function MouseIcon(container:DisplayObjectContainer)
		{			
			m_container = container;
			m_container.addEventListener(MouseEvent.MOUSE_MOVE, onMouseMove);
			m_sprite = new Sprite();
			m_sprite.name = k_MOUSE_ICON_NAME;
            m_sprite.mouseEnabled = false;
            m_sprite.mouseChildren = false;
            
            if(s_point == null)
            {
            	s_point = new Point();
            }
		}
		
		public function release():void
		{			
			m_container.removeEventListener(MouseEvent.MOUSE_MOVE, onMouseMove);
		}
				
		public function setStaticIcon(icon:Sprite):void
		{			
			removeStaticIcon();
						
			m_staticIcon = icon;			
			m_sprite.addChild(m_staticIcon);
			m_container.addChild(m_sprite);
		}
		
		private function removeStaticIcon():void
		{
			if(m_staticIcon != null)
			{
				m_sprite.removeChild(m_staticIcon);
				m_staticIcon = null;
			}
		}
		
		protected function onLoadIcon(data:BitmapData):void
		{
			//removeStaticIcon();
			releaseLoadedIcon();
			
			if (m_loadedIcon == null) 
			{
				m_loadedIcon = new Bitmap();
			}
			m_loadedIcon.bitmapData = data;			
			m_sprite.addChild(m_loadedIcon);
			m_container.addChild(m_sprite);
		}
		
		public function releaseLoadedIcon():void
		{			
			if(m_loadedIcon != null)
			{
				m_sprite.removeChild(m_loadedIcon);
				m_loadedIcon = null;
			}
		}
		
		public function setOffsets(x:int, y:int):void
		{
			m_offsetX = x;
			m_offsetY = y;
		}
		
		private function onMouseMove(e:MouseEvent):void
		{
			s_point.x = Global.stage.mouseX;
			s_point.y = Global.stage.mouseY;
			m_container.globalToLocal(s_point);
			m_sprite.x = s_point.x + m_offsetX;
			m_sprite.y = s_point.y + m_offsetY;
		}
		
	}
}