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
			m_meshHalf = _meshHalf;
		}
		
		override protected function onResLoad(_data:BitmapData):void 
		{
			/*m_texture.size = new Point(_data.width / Level.k_MAP_WIDTH, _data.height / Level.k_MAP_HEIGHT);
			m_bitamData = new BitmapData(_data.width / Level.k_MAP_WIDTH, _data.height / Level.k_MAP_HEIGHT);
			m_bitamData.copyPixels(_data, new Rectangle( m_index.x * m_bitamData.width, m_index.y * m_bitamData.height, m_bitamData.width, m_bitamData.height), new Point(0, 0));
			m_texture.bitmapData = m_bitamData;*/
			
			//m_bitamData = _data;
			m_bitamData = new BitmapData(_data.width / 2, _data.height);
			m_bitamData.copyPixels(_data, new Rectangle( m_meshHalf * m_bitamData.width, 0, m_bitamData.width, m_bitamData.height), new Point(0, 0));
			m_texture.size = new Point(m_bitamData.width , m_bitamData.height);
			m_texture.bitmapData = m_bitamData;
		}
	}
}