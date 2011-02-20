package common.helper3d
{
	import common.loader.ContentLoader;
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.display.MovieClip;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.filters.GlowFilter;
	import flash.geom.ColorTransform;
	import flash.geom.Matrix;
	import flash.geom.Point;
	import flash.display.Loader;
	import flash.geom.Rectangle;
	import flash.geom.Vector3D;
	import flash.net.URLLoader;
	import flash.net.URLRequest;
	

	public class Sprite3d extends Sprite
	{
		protected var m_position:Vector3D = new Vector3D();
		protected var m_rotation:Vector3D = new Vector3D();
		protected var m_size:Point = new Point();
		
		protected var m_wspLeftTop:Vector3D = new Vector3D();				
		protected var m_wspLeftBottom:Vector3D = new Vector3D();
		protected var m_wspRightTop:Vector3D = new Vector3D();	
		protected var m_wspRightBottom:Vector3D = new Vector3D();
		
		protected var m_sspLeftTop:Point = new Point();				
		protected var m_sspLeftBottom:Point = new Point();
		protected var m_sspRightTop:Point = new Point();
		protected var m_sspRightBottom:Point = new Point();
		
		protected var m_texture:Texture = null;
		
		protected var m_container:DisplayObjectContainer = null;
		protected var m_loader:ContentLoader = null;
		
		protected var m_index:Point = null;
		
		public var m_zIndex:int = 0;
		
		public function set Position(_value:Vector3D):void
		{
			m_position = _value;
			m_zIndex = m_position.z;
		}
		
		public function get Position():Vector3D
		{
			return m_position;
		}
		
		public function set Rotation(_value:Vector3D):void
		{
			m_rotation = _value;
		}
		
		public function get Rotation():Vector3D
		{
			return m_rotation;
		}
		
		public function Sprite3d(_container:DisplayObjectContainer,_loader:ContentLoader, _index:Point, _size:Point) 
		{
			m_container = _container;
			
			m_loader = _loader;
			
			m_size = _size;
			
			m_index = _index;
			
			m_texture = new Texture(this, new Point(128, 141));
			
			init();
		}
		
		private function init():void
		{
			addEventListener(MouseEvent.MOUSE_OVER, onMouseOver);
			addEventListener(MouseEvent.MOUSE_OUT, onMouseOut);
		}
		
		private function onMouseOver(_event:MouseEvent):void
		{
			transform.colorTransform = new ColorTransform(0, 1, 0);
		}
		
		private function onMouseOut(_event:MouseEvent):void
		{
			transform.colorTransform = new ColorTransform(1, 1, 1);
		}

		public function rasterize():void
		{
			var mapBD:BitmapData = m_loader.imagesManager["TreasureMap"];
			
			if (mapBD == null)
			{
				return;
			}
			
			var partBD:BitmapData = new BitmapData(mapBD.width / Main.k_MAP_WIDTH, mapBD.height / Main.k_MAP_HEIGHT);
			partBD.copyPixels(mapBD, new Rectangle(m_index.x * partBD.width,  m_index.y * partBD.height, partBD.width, partBD.height), new Point(0,0));
			m_texture.bitmapData = partBD;
			m_texture.transform(m_sspLeftBottom, m_sspRightBottom, m_sspRightTop, m_sspLeftTop);
			m_texture.rasterize();
		}
		
		public function update():void
		{
			updateObjectSpace();
			updateWorldSpace();
			updateScreenSpace();
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
			var mRX:Matrix3d = Matrix3d.matrixRotateX(m_rotation.x);
		    var mRY:Matrix3d = Matrix3d.matrixRotateY(m_rotation.y);
			var mRZ:Matrix3d = Matrix3d.matrixRotateZ(m_rotation.z);
			
			m_wspLeftBottom  = Matrix3d.matrixMulVector(m_wspLeftBottom, mRX);
			m_wspLeftTop     = Matrix3d.matrixMulVector(m_wspLeftTop, mRX);
			m_wspRightBottom = Matrix3d.matrixMulVector(m_wspRightBottom, mRX);
			m_wspRightTop    = Matrix3d.matrixMulVector(m_wspRightTop, mRX);
			
			m_wspLeftBottom  = Matrix3d.matrixMulVector(m_wspLeftBottom, mRY);
			m_wspLeftTop     = Matrix3d.matrixMulVector(m_wspLeftTop, mRY);
			m_wspRightBottom = Matrix3d.matrixMulVector(m_wspRightBottom, mRY);
			m_wspRightTop    = Matrix3d.matrixMulVector(m_wspRightTop, mRY);
			
			m_wspLeftBottom  = Matrix3d.matrixMulVector(m_wspLeftBottom, mRZ);
			m_wspLeftTop     = Matrix3d.matrixMulVector(m_wspLeftTop, mRZ);
			m_wspRightBottom = Matrix3d.matrixMulVector(m_wspRightBottom, mRZ);
			m_wspRightTop    = Matrix3d.matrixMulVector(m_wspRightTop, mRZ);
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