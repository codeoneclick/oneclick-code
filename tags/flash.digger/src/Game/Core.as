package Game 
{
	import Common.ResourceManager;
	/**
	 * ...
	 * @author ...
	 */
	public class Core 
	{
		private static var m_resourceManager:ResourceManager = null;
		
		public static function get resourceManager():ResourceManager
		{
			if (m_resourceManager == null)
			{
				m_resourceManager = new ResourceManager();				
			}
			return m_resourceManager;
		}
		
	}

}