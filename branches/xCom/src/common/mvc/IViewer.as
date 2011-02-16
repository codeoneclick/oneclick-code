package common.mvc 
{
	import common.content.ContentEvent;
	import common.content.ContentLoader;
	import common.helper3d.Sprite3d;
	import common.helper3d.Texture;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.Loader;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.IOErrorEvent;
	import flash.geom.Point;
	import flash.net.URLRequest;
	import Game.Core;
	/**
	 * ...
	 * @author ...
	 */
	public class IViewer extends Sprite3d
	{
		private var m_url:String = "";
		private var m_dataType:String = "";
		
		public function IViewer(_url:String, _dataType:String) 
		{
			m_url = _url;
			m_dataType = _dataType;
			init();
		}
		
		private function init():void
		{
			if (m_dataType == ContentLoader.k_SWF_DATA)
			{
				addEventListener(ContentEvent.k_LOAD_SWF_DATA, onLoadCompleted);
			}
			else if (m_dataType == ContentLoader.k_BITMAP_DATA)
			{
				addEventListener(ContentEvent.k_LOAD_BITMAP_DATA, onLoadCompleted);
			}
			
			Core.contentLoader.request(m_url, this);	
		}
		
		private function onLoadCompleted(_event:IEvent):void
		{
			if (m_dataType == ContentLoader.k_SWF_DATA)
			{
				addChild(new _event.data.content);
			}
			else if (m_dataType == ContentLoader.k_BITMAP_DATA)
			{
				var bitmapData:BitmapData = _event.data.content;
				m_texture = new Texture(this, new Point(32, 32));
				m_texture.bitmapData = bitmapData;
				m_size = new Point(32, 32);
				//addChild(new Bitmap(bitmapData));
			}
			
			addEventListener(Event.ENTER_FRAME, update);
		}
		
		protected function update(_event:Event):void
		{
			updateObjectSpace();
			updateWorldSpace();
			updateScreenSpace();
			m_texture.transform(m_sspLeftBottom, m_sspRightBottom, m_sspRightTop, m_sspLeftTop);
			m_texture.rasterize();
		}
		
		private function updateObjectSpace():void
		{
			m_wspLeftTop.z = 0;
			m_wspLeftTop.x = 0;
			m_wspLeftTop.y = 0;

			m_wspRightTop.z = 0;
			m_wspRightTop.x = m_size.x / 2;
			m_wspRightTop.y = 0;

			m_wspLeftBottom.z = 0;
			m_wspLeftBottom.x = 0;
			m_wspLeftBottom.y = m_size.y / 2;

			m_wspRightBottom.z = 0;
			m_wspRightBottom.x = m_size.x / 2;
			m_wspRightBottom.y = m_size.y / 2;
		}
		
		private function updateWorldSpace():void
		{
			rotate();
			translate();
		}
		
		private function updateScreenSpace():void
		{
			var d:Number = 1;
			
			var ar:Number = 800 / 600;
			
			m_sspLeftBottom.x = m_wspLeftBottom.x * d / m_wspLeftBottom.z;
			m_sspLeftBottom.y = m_wspLeftBottom.y * d  * ar / m_wspLeftBottom.z;
			
			m_sspLeftTop.x = m_wspLeftTop.x * d / m_wspLeftTop.z;
			m_sspLeftTop.y = m_wspLeftTop.y * d * ar  / m_wspLeftTop.z;
			
			m_sspRightBottom.x = m_wspRightBottom.x * d / m_wspRightBottom.z;
			m_sspRightBottom.y = m_wspRightBottom.y * d  * ar  / m_wspRightBottom.z;
			
			m_sspRightTop.x = m_wspRightTop.x * d / m_wspRightTop.z;
			m_sspRightTop.y = m_wspRightTop.y * d  * ar  / m_wspRightTop.z;

			
			m_sspLeftBottom.x = (m_sspLeftBottom.x + 1) * (0.5 * 800 - 0.5);
			m_sspLeftBottom.y = ( 600 - 1 ) - ( m_sspLeftBottom.y + 1 ) * ( 0.5 * 600 - 0.5); 
			
			m_sspLeftTop.x = (m_sspLeftTop.x + 1) * (0.5 * 800 - 0.5);
			m_sspLeftTop.y = ( 600 - 1 ) - ( m_sspLeftTop.y + 1 ) * ( 0.5 * 600 - 0.5); 
			
			m_sspRightBottom.x = (m_sspRightBottom.x + 1) * (0.5 * 800 - 0.5);
			m_sspRightBottom.y = ( 600 - 1 ) - ( m_sspRightBottom.y + 1 ) * ( 0.5 * 600 - 0.5); 
			
			m_sspRightTop.x = (m_sspRightTop.x + 1) * (0.5 * 800 - 0.5);
			m_sspRightTop.y = ( 600 - 1 ) - ( m_sspRightTop.y + 1 ) * ( 0.5 * 600 - 0.5); 
		}
		
		private function rotate():void
		{
			
		}
		
		private function translate():void
		{
			m_wspLeftTop.x += m_position.x;
			m_wspLeftTop.y += m_position.y;
			m_wspLeftTop.z += m_position.z;
			
			m_wspRightTop.x += m_position.x;
			m_wspRightTop.y += m_position.y;
			m_wspRightTop.z += m_position.z;
			
			m_wspLeftBottom.x += m_position.x;
			m_wspLeftBottom.y += m_position.y;
			m_wspLeftBottom.z += m_position.z;
			
			m_wspRightBottom.x += m_position.x;
			m_wspRightBottom.y += m_position.y;
			m_wspRightBottom.z += m_position.z;
		}
	}

}