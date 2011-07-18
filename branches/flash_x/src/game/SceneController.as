package game 
{
	import core.Global;
	import fl.controls.Button;
	import flash.display.Sprite;
	import flash.geom.Point;
	import flash.utils.Dictionary;
	/**
	 * ...
	 * @author codeoneclick
	 */
	public class SceneController 
	{	
		private static const k_DEFAULT_LAYER:String = "DEFAULT_LAYER";
		private static const k_SECTOR_INDEX:String = "SECTOR_INDEX";
		
		private var m_gameNodeContainer:Vector.<GameNode> = new Vector.<GameNode>();
		private var m_characterNode:Character = null;
		
		private var m_mapContainer:Dictionary = new Dictionary();
		
		private var m_visualLayers:Dictionary = new Dictionary();	
		
		private var m_background:Background = null;
		
		public function SceneController() 
		{
			m_background = new Background(Global.backContainer);
			m_background.Load("back_02");
		}
		
		public function initDefault():void
		{
			m_visualLayers[k_DEFAULT_LAYER] = new LayerContainer(k_DEFAULT_LAYER);
			Global.inGameContainer.addChild(m_visualLayers[k_DEFAULT_LAYER]);
			Global.editorController.addSector(new Point(0, 0), "sector_01", Sector.k_SECTOR_MIDDLE);
		}
		
		public function addSector(_position:Point, _sectorName:String, _sectorType:String):Boolean
		{
			
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] != null && m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] != null )
			{
				changeSector(_position, _sectorName, _sectorType);
				return false;
			}
			
			
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] == null)
			{
				 m_mapContainer[k_SECTOR_INDEX + _position.x] = new Dictionary();
			}
			
			m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] = new Sector(m_visualLayers[k_DEFAULT_LAYER]);
			m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].Load(_sectorName, _sectorType);
			calculatePosition(_position);
			m_gameNodeContainer.push(m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y]);
			m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].index = new Point(_position.x, _position.y);
			
			return true;
		}
		
		public function addSubSectors(_position:Point):void
		{
			
			Global.sceneController.addSubSector( new Point(_position.x, _position.y - 2) );
			Global.sceneController.addSubSector( new Point(_position.x, _position.y + 2) );
				
			Global.sceneController.addSubSector( new Point(_position.x - 1, _position.y) );
			Global.sceneController.addSubSector( new Point(_position.x + 1, _position.y) );
				
			Global.sceneController.addSubSector( new Point(_position.x, _position.y - 1) );
			Global.sceneController.addSubSector( new Point(_position.x, _position.y + 1) );
			
			if (Math.abs(_position.y) % 2 > 0)
			{	
				Global.sceneController.addSubSector( new Point(_position.x - 1, _position.y - 1) );
				Global.sceneController.addSubSector( new Point(_position.x - 1, _position.y + 1) );
			}
			else
			{
				Global.sceneController.addSubSector( new Point(_position.x + 1, _position.y - 1) );
				Global.sceneController.addSubSector( new Point(_position.x + 1, _position.y + 1) );
			}
		}
		
		private function addSubSector(_position:Point):void
		{
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] == null )
			{
				m_mapContainer[k_SECTOR_INDEX + _position.x] = new Dictionary();
			}
						
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] == null)
			{
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] = new Sector(m_visualLayers[k_DEFAULT_LAYER]);
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].Load(Sector.k_SECTOR_DEFAULT_NAME, Sector.k_SECTOR_MIDDLE);
				calculatePosition(new Point(_position.x , _position.y));
				m_gameNodeContainer.push(m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y]);
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].index = new Point(_position.x,_position.y);
			}
		}
		
		public function zOrder():void
		{
			m_gameNodeContainer.sort(GameNode.sorter);
			for (var i:int = 0; i < m_gameNodeContainer.length; i++)
			{
				m_visualLayers[k_DEFAULT_LAYER].setChildIndex(m_gameNodeContainer[i], i);
			}	
		}	
		
		public function changeSector(_position:Point, _sectorName:String, _sectorType:String):Boolean
		{
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x] == null )
			{
				return false;
			}
			
			if ( m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y] == null )
			{
				return false;
			}
			
			m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].Load(_sectorName, _sectorType);
			
			return true;
		}
		
		private function calculatePosition(_position:Point):void
		{
			if ( Math.abs(_position.y) % 2 > 0 )
			{
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].position.x = _position.x * Sector.k_SECTOR_WIDTH;
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].position.y = _position.y * Sector.k_SECTOR_HEIGHT / 2;
			}
			else
			{
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].position.x = _position.x * Sector.k_SECTOR_WIDTH + Sector.k_SECTOR_WIDTH / 2;
				m_mapContainer[k_SECTOR_INDEX + _position.x][k_SECTOR_INDEX + _position.y].position.y = _position.y * Sector.k_SECTOR_HEIGHT / 2;
			}
		}
		
		/*public function createLayer(_width:int, _height:int, _name:String):void
		{
			m_visualLayers[_name] = new LayerContainer(_name);
			Global.inGameContainer.addChild(m_visualLayers[_name]);
			createMap( _width, _height, (m_visualLayers[_name] as LayerContainer).getSubLayer(LayerContainer.k_TILE_LAYER) );
			createMap( _width, _height, (m_visualLayers[_name] as LayerContainer).getSubLayer(LayerContainer.k_OBJECT_LAYER) );
		}
		
		private function createMap(_width:int, _height:int, _container:Sprite):void
		{
			for ( var j:int = 0; j < _height; j++ )
			{
				for ( var i:int = 0; i < _width; i++ )
				{	
					m_gameNodeContainer[i] = new GameNode(_container);
					m_gameNodeContainer[i].Load("tile_04", GameNode.k_SECTOR_MIDDLE);
					if ( j % 2 > 0 )
					{
						m_gameNodeContainer[i].position.x = i * k_TILE_WIDTH;
						m_gameNodeContainer[i].position.y = j * k_TILE_HEIGHT / 2;
					}
					else
					{
						m_gameNodeContainer[i].position.x = i * k_TILE_WIDTH + k_TILE_WIDTH / 2;
						m_gameNodeContainer[i].position.y = j * k_TILE_HEIGHT / 2;
					}
				}
			}
		}*/
		
	}

}