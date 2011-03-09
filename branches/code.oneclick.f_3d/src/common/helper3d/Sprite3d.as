package common.helper3d
{
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
	import game.Core;
	

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
		
		protected var m_parent:Container3d = null;
			
		public function set Position(_value:Vector3D):void
		{
			m_position = _value;
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
		
		public function set Parent(_value:Container3d):void
		{
			m_parent = _value;
		}
		
		public function get Parent():Container3d
		{
			return m_parent;
		}
		
		public function Sprite3d(_container:DisplayObjectContainer, _size:Point) 
		{
			m_container = _container;
			
			m_size = _size;
			
			m_texture = new Texture(this);
			
			init();
		}
		
		private function init():void
		{
			m_container.addChild(this);
			
			addEventListener(MouseEvent.MOUSE_OVER, onMouseOver);
			addEventListener(MouseEvent.MOUSE_OUT, onMouseOut);
		}
		
		protected function onMouseOver(_event:MouseEvent):void
		{
			
		}
		
		protected function onMouseOut(_event:MouseEvent):void
		{
			
		}
		
		protected function updateCulling():void
		{
			if (m_wspLeftBottom.z < 0 || m_wspLeftTop.z < 0 || m_wspRightBottom.z < 0 || m_wspRightTop.z < 0)
				visible = false;
			else
				visible = true;
		}

		protected function rasterize():void
		{
			if (visible)
			{
				m_texture.transform(m_sspLeftBottom, m_sspRightBottom, m_sspRightTop, m_sspLeftTop);
				m_texture.rasterize();
			}
		}
		
		protected function update():void
		{
			updateObjectSpace();
			updateWorldSpace();
			updateCulling();
			updateScreenSpace();
		}
		
		private function updateObjectSpace():void
		{
			m_wspLeftTop.z = 0;
			m_wspLeftTop.x = 0;
			m_wspLeftTop.y = 0;

			m_wspRightTop.z = 0;
			m_wspRightTop.x = m_size.x;
			m_wspRightTop.y = 0;

			m_wspLeftBottom.z = 0;
			m_wspLeftBottom.x = 0;
			m_wspLeftBottom.y = m_size.y;

			m_wspRightBottom.z = 0;
			m_wspRightBottom.x = m_size.x;
			m_wspRightBottom.y = m_size.y;
		}
		
		private function updateWorldSpace():void
		{
			rotate(m_rotation);
			translate(m_position);
			
			var container:Container3d = m_parent;
			while (container != null)
			{
				rotate(container.Rotation);
				translate(container.Position);
				container = container.Parent;
			}
		}
		
		private function updateScreenSpace():void
		{
			m_sspLeftBottom.x = m_wspLeftBottom.x * Core.camera.Fov / m_wspLeftBottom.z;
			m_sspLeftBottom.y = m_wspLeftBottom.y * Core.camera.Fov  * Core.camera.AspectRatio / m_wspLeftBottom.z;
			
			m_sspLeftTop.x = m_wspLeftTop.x * Core.camera.Fov / m_wspLeftTop.z;
			m_sspLeftTop.y = m_wspLeftTop.y * Core.camera.Fov * Core.camera.AspectRatio  / m_wspLeftTop.z;
			
			m_sspRightBottom.x = m_wspRightBottom.x * Core.camera.Fov / m_wspRightBottom.z;
			m_sspRightBottom.y = m_wspRightBottom.y * Core.camera.Fov  * Core.camera.AspectRatio  / m_wspRightBottom.z;
			
			m_sspRightTop.x = m_wspRightTop.x * Core.camera.Fov / m_wspRightTop.z;
			m_sspRightTop.y = m_wspRightTop.y * Core.camera.Fov * Core.camera.AspectRatio  / m_wspRightTop.z;

			
			m_sspLeftBottom.x = ( m_sspLeftBottom.x + 1) * (0.5 * Core.camera.ScreenWidth - 0.5);
			m_sspLeftBottom.y = ( Core.camera.ScreenHeight - 1 ) - ( m_sspLeftBottom.y + 1 ) * ( 0.5 * Core.camera.ScreenHeight - 0.5); 
			
			m_sspLeftTop.x = ( m_sspLeftTop.x + 1) * (0.5 * Core.camera.ScreenWidth - 0.5);
			m_sspLeftTop.y = ( Core.camera.ScreenHeight - 1 ) - ( m_sspLeftTop.y + 1 ) * ( 0.5 * Core.camera.ScreenHeight - 0.5); 
			
			m_sspRightBottom.x = ( m_sspRightBottom.x + 1) * (0.5 * Core.camera.ScreenWidth - 0.5);
			m_sspRightBottom.y = ( Core.camera.ScreenHeight - 1 ) - ( m_sspRightBottom.y + 1 ) * ( 0.5 * Core.camera.ScreenHeight - 0.5); 
			
			m_sspRightTop.x = ( m_sspRightTop.x + 1) * ( 0.5 * Core.camera.ScreenWidth - 0.5 );
			m_sspRightTop.y = ( Core.camera.ScreenHeight - 1 ) - ( m_sspRightTop.y + 1 ) * ( 0.5 * Core.camera.ScreenHeight - 0.5); 
		}
		
		private function rotate(_vector:Vector3D):void
		{
			var mRX:Matrix3d = Matrix3d.matrixRotateX(_vector.x);
		    var mRY:Matrix3d = Matrix3d.matrixRotateY(_vector.y);
			var mRZ:Matrix3d = Matrix3d.matrixRotateZ(_vector.z);
			
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
		
		private function translate(_vector:Vector3D):void
		{
			m_wspLeftTop.x += _vector.x;
			m_wspLeftTop.y += _vector.y;
			m_wspLeftTop.z += _vector.z;
			
			m_wspRightTop.x += _vector.x;
			m_wspRightTop.y += _vector.y;
			m_wspRightTop.z += _vector.z;
			
			m_wspLeftBottom.x += _vector.x;
			m_wspLeftBottom.y += _vector.y;
			m_wspLeftBottom.z += _vector.z;
			
			m_wspRightBottom.x += _vector.x;
			m_wspRightBottom.y += _vector.y;
			m_wspRightBottom.z += _vector.z;
		}
	}
}