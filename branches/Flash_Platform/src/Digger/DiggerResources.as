package Digger 
{
	/**
	 * ...
	 * @author ...
	 */
	public class DiggerResources
	{
		public static function Load():void
		{
			Resource.m_ContentLoader.LoadPNG("element_ground");
			Resource.m_ContentLoader.LoadPNG("element_player");
			Resource.m_ContentLoader.LoadPNG("element_empty");
			Resource.m_ContentLoader.LoadPNG("element_empty_01");
			Resource.m_ContentLoader.LoadPNG("element_stone");
			Resource.m_ContentLoader.LoadPNG("element_stone_01");
			Resource.m_ContentLoader.LoadPNG("element_enemy");
			Resource.m_ContentLoader.LoadPNG("element_explosion");
			Resource.m_ContentLoader.Start();
		}
		
	}

}