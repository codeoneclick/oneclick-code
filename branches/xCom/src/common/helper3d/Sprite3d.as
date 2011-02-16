package common.helper3d 
{
	import flash.display.Sprite;
	import flash.geom.Point;
	import flash.geom.Vector3D;
	/**
	 * ...
	 * @author ...
	 */
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
		
		public function Sprite3d() 
		{
			
		}
		
		public function set position(_value:Vector3D):void
		{
			m_position = _value;
		}
		
	}

}