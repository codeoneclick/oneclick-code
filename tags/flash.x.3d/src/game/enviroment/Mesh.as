package game.enviroment 
{
	import common.helper3d.Container3d;
	import flash.display.DisplayObjectContainer;
	import flash.geom.Point;
	import flash.geom.Vector3D;
	/**
	 * ...
	 * @author ...
	 */
	public class Mesh 
	{
		private static const k_MAX_MESH_NODE:int = 4;
		protected var m_meshNodeList:Vector.<MeshNode> = new Vector.<MeshNode>();
		protected var m_position:Vector3D = new Vector3D();
		protected var m_rotation:Vector3D = new Vector3D();
	
		private static var i:int = 0;
		
		public function Mesh(_container:DisplayObjectContainer, _size:Point, _resName:String, _zOrderSortContainer:Vector.<SimpleNode>, _parentContainer:Container3d = null) 
		{
			for ( i = 0; i < k_MAX_MESH_NODE; i++)
			{
				if ((i % 2) == 0)
				{
					m_meshNodeList.push(new MeshNode(_container, _size, _resName, MeshNode.k_MESH_HALF_01));
				}
				else
				{
					m_meshNodeList.push(new MeshNode(_container, _size, _resName, MeshNode.k_MESH_HALF_02));
				}
					
				m_meshNodeList[i].Parent = _parentContainer;
				_zOrderSortContainer.push(m_meshNodeList[i]);
			}
		}
		
		public function set Position(_value:Vector3D):void
		{
			m_position = _value;
			for ( i = 0; i < k_MAX_MESH_NODE; i++)
			{
				m_meshNodeList[i].Position = new Vector3D(m_position.x, m_position.y, m_position.z);
			}	
			
			m_meshNodeList[0].Position.x += m_meshNodeList[0].Size.x / 2;
			m_meshNodeList[1].Position.x -= m_meshNodeList[1].Size.x / 2;
			
			m_meshNodeList[2].Rotation.y = 1.57;
			m_meshNodeList[2].Position.z += m_meshNodeList[2].Size.x / 2;

			m_meshNodeList[3].Rotation.y = 1.57;
			m_meshNodeList[3].Position.z -= m_meshNodeList[3].Size.x / 2;
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
		
	}

}