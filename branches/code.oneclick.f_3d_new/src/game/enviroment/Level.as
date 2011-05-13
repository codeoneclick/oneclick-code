package game.enviroment 
{
	import common.helper3d.Container3d;
	import common.helper3d.Sprite3d;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.geom.Point;
	import flash.geom.Vector3D;
	import flash.utils.Dictionary;
	import game.core.Core;
	/**
	 * ...
	 * @author ...
	 */
	public class Level 
	{
		public static const k_MAP_WIDTH:int  = 12;
		public static const k_MAP_HEIGHT:int = 12;
		public static const k_DECO_OFFSET:int = 2;
		
		private var m_mapContainer:Container3d = new Container3d();
		
		private var m_zOrderSortingNodes:Vector.<SimpleNode> = new Vector.<SimpleNode>();
		
		private var m_zOrderSortLayer:Sprite = new Sprite();
		private var m_zOrderNoSortLayer:Sprite = new Sprite();
		
		private static var i:int = 0;
		private static var j:int = 0;
		
		public function Level() 
		{
			init();
		}
		
		private function init():void
		{
			Core.displayContainer.addChild(m_zOrderNoSortLayer);
			Core.displayContainer.addChild(m_zOrderSortLayer);
			
			var workingGroundCell:Plane = null;
			var workingDecoCell:Decoration = null;
			var workingCharacterCell:Mesh = null;
			
			for ( i = 0; i < k_MAP_WIDTH; i++)
			{
				for ( j = 0; j < k_MAP_HEIGHT; j++)
				{
					workingGroundCell = new Plane(m_zOrderNoSortLayer, new Point(Plane.k_WIDTH, Plane.k_HEIGHT), "grn_cell");
					workingGroundCell.Parent = m_mapContainer;
					workingGroundCell.Rotation.x = 1.57;
					workingGroundCell.Position.x = Plane.k_WIDTH * i - Plane.k_WIDTH * (k_MAP_WIDTH  - 1) / 2;
					workingGroundCell.Position.z = Plane.k_HEIGHT * j - Plane.k_HEIGHT * (k_MAP_HEIGHT - 1) / 2;
					
					if (i < k_DECO_OFFSET || j < k_DECO_OFFSET || i >= (k_MAP_WIDTH - k_DECO_OFFSET) || j >= (k_MAP_HEIGHT - k_DECO_OFFSET))
					{
						/*workingDecoCell = new Decoration(m_zOrderSortLayer, new Point(Plane.k_WIDTH / 2, Plane.k_HEIGHT / 2), "deco_cell_pic");
						workingDecoCell.Parent = m_mapContainer;
						workingDecoCell.Rotation.y = 0;
						workingDecoCell.Position.x = Plane.k_WIDTH * i - Plane.k_WIDTH * (k_MAP_WIDTH  - 1) / 2;
						workingDecoCell.Position.z = Plane.k_HEIGHT * j - Plane.k_HEIGHT * (k_MAP_HEIGHT - 1) / 2;
						workingDecoCell.Position.y = Plane.k_WIDTH / 4;
						m_zOrderSortingNodes.push(workingDecoCell);*/
					}
					else
					{
						workingCharacterCell = new Mesh(m_zOrderSortLayer, new Point(Plane.k_WIDTH / 2 , Plane.k_HEIGHT ), "box_cell",m_zOrderSortingNodes,m_mapContainer);
						workingCharacterCell.Position = new Vector3D(Plane.k_WIDTH * i - Plane.k_WIDTH * (k_MAP_WIDTH  - 1) / 2,Plane.k_WIDTH / 2,Plane.k_HEIGHT * j - Plane.k_HEIGHT * (k_MAP_HEIGHT - 1) / 2);
					}
				}
			}			
			
			Core.stage.addEventListener(Event.ENTER_FRAME, update);
		}
		
		private function update(_event:Event):void
		{
			m_mapContainer.Position = Core.camera.Position;
			m_mapContainer.Rotation.y += 0.027;
			zOrder();
		}
		
		private function zOrder():void
		{
			m_zOrderSortingNodes.sort(Sprite3d.sprite3dSorter);
			for ( i = 0; i < m_zOrderSortingNodes.length; i++)
			{
				m_zOrderSortLayer.setChildIndex(m_zOrderSortingNodes[i], i);
				//m_zOrderSortingNodes[i].Rotation.y = -m_rotationY;
			}	
		}	
	}
}