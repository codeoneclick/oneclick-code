package game.enviroment 
{
	import flash.display.BitmapData;
	import flash.display.DisplayObjectContainer;
	import flash.filters.DropShadowFilter;
	import flash.geom.Point;
	import flash.geom.Rectangle;
	/**
	 * ...
	 * @author ...
	 */
	public class MeshNode extends SimpleNode
	{
		public static const k_MESH_HALF_01:int = 0;
		public static const k_MESH_HALF_02:int = 1;
		
		private var m_meshHalf:int = 0;
		
		public function MeshNode(_container:DisplayObjectContainer, _size:Point, _resName:String, _meshHalf:int) 
		{
			super(_container, _size, _resName);
		}
	}
}