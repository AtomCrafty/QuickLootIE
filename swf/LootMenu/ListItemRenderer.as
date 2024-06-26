﻿class LootMenu.ListItemRenderer extends gfx.controls.ListItemRenderer
{
	/* PRIVATE VARIABLES */

	private static var RED: Number = 0xEF9A9A;
	private static var WHITE: Number = 0xFFFFFF;
	private var _iconLabel: String;
	private var _iconSource: String;


	/* STAGE ELEMENTS */

	public var textField: TextField;
	public var dbmNew: MovieClip;
	public var dbmFound: MovieClip;
	public var dbmDisp: MovieClip;
	
	public var compNew: MovieClip;
	public var compFnd: MovieClip;
	
	public var itemIcon: MovieClip;
	public var stolenIcon: MovieClip;
	public var enchantIcon: MovieClip;
	public var knownEnchantIcon: MovieClip;
	public var specialEnchantIcon: MovieClip;
	public var readIcon: MovieClip;
	public var itemWeight: TextField;
	public var itemValue: TextField;
	public var itemValuePerWeight: TextField;


	/* INITIALIZATION */

	// @override gfx.controls.ListItemRenderer
	public function ListItemRenderer(a_obj: Object)
	{
		super();
		dbmNew._visible = false;
		dbmFound._visible = false;
		dbmDisp._visible = false;
		
		compNew._visible = false;
		compFnd._visible = false;
		
		_iconSource = "skyui/icons_item_psychosteve.swf";

		var iconLoader = new MovieClipLoader();
		iconLoader.addListener(this);
		iconLoader.loadClip(_iconSource, itemIcon);
		itemIcon._visible = false;
		stolenIcon._visible = false;
		enchantIcon._visible = false;
		knownEnchantIcon._visible = false;
		specialEnchantIcon._visible = false;
		readIcon._visible = false;
		itemWeight._visible = false;
		itemValue._visible = false;
		itemValuePerWeight._visible = false;
	}


	/* PUBLIC FUNCTIONS */

	/**
	 * @override gfx.controls.ListItemRenderer
	 *
	 * @param a_data
	 * 	displayName: String
	 * 	count: Number
	 *	stolen: Boolean
	 */
	public function setData(a_data: Object): Void
	{
		super.setData(a_data);
		
		if (data == null) {
			return;
		}

		skse.plugins.InventoryInjector.ProcessEntry(data);
		var iconSource =
			data.iconSource != undefined ? data.iconSource : "skyui/icons_item_psychosteve.swf";
		if (iconSource != _iconSource) {
			_iconSource = iconSource;
			var iconLoader = new MovieClipLoader();
			iconLoader.addListener(this);
			iconLoader.loadClip(_iconSource, itemIcon);
		}

		var displayName: String = data.displayName != null ? data.displayName : "";	  
		var count: Number = data.count != null ? data.count : 1;
		var stolen: Boolean = data.stolen != null ? data.stolen : false;
		var weight: Number = data.weight != null ? data.weight : 0;
		var value: Number = data.value != null ? data.value : 0

		if (count > 1) {
			displayName += " (" + count.toString() + ")";
		}

		var maxTextLength: Number = 32;
		if (displayName.length > maxTextLength) {
			displayName = displayName.substr(0, maxTextLength - 3) + "...";
		}
		
		var setPrecision:Function = function(number:Number, precision:Number) {
 			precision = Math.pow(10, precision);
 			return Math.round(number * precision)/precision;
		}
		
		if (data.weight != null) {
			itemWeight.text = setPrecision(weight, 2).toString();
			itemWeight._visible = true;
		}
		
		if (data.value != null) {
			itemValue.text = setPrecision(value, 2).toString();
			itemValue._visible = true;
		}
		
		this.itemValuePerWeight.text = setPrecision(weight / value, 0).toString()
		this.itemValuePerWeight._visible = true;

		label = displayName;
		
		textField.autoSize = "left";
		textField.textColor = stolen ? RED : (data.textColor != undefined ? data.textColor : WHITE);
		
		var iconPosX = textField._x + textField._width + 3;
		var iconSpacing = 3;
		
		stolenIcon._visible = (data.stolen != undefined && data.stolen);
		if (stolenIcon._visible)
		{
			stolenIcon._x = iconPosX;
			iconPosX += stolenIcon._width + iconSpacing;
		}
		
		var enchanted: Boolean = (data.enchanted != undefined && data.enchanted);
		if (enchanted)
		{
			var known_enchanted: Boolean = (data.knownEnchanted != undefined && data.knownEnchanted);
			var special_enchanted: Boolean = (data.specialEnchanted != undefined && data.specialEnchanted);
			
			if (known_enchanted)
			{
				knownEnchantIcon._visible = true;
				knownEnchantIcon._x = iconPosX;
				iconPosX += knownEnchantIcon._width + iconSpacing;
			} 
			else if(special_enchanted)
			{
				specialEnchantIcon._visible = true;
				specialEnchantIcon._x = iconPosX;
				iconPosX += specialEnchantIcon._width + iconSpacing;
			}
			else
			{
				enchantIcon._visible = true;
				enchantIcon._x = iconPosX;
				iconPosX += enchantIcon._width + iconSpacing;
			}
		}

		readIcon._visible = (data.isRead != undefined && data.isRead);
		if (readIcon._visible)
		{
			readIcon._x = iconPosX;
			iconPosX += readIcon._width + iconSpacing;
		}

		if (data.dbmNew == true) {
			dbmNew._visible = true;
			dbmNew._x = iconPosX;
			iconPosX += dbmNew._width + iconSpacing;
		} else if (data.dbmDisp == true) {
			dbmDisp._visible = true;
			dbmDisp._x = iconPosX;
			iconPosX += dbmDisp._width + iconSpacing;
		} else if (data.dbmFound == true) {
			dbmFound._visible = true;
			dbmFound._x = iconPosX;
			iconPosX += dbmFound._width + iconSpacing;
		}

		if (data.compNew == true) {
			compNew._visible = true;
			compNew._x = iconPosX;
			iconPosX += compNew._width + iconSpacing;
		} else if (data.compFnd == true) {
			compFnd._visible = true;
			compFnd._x = iconPosX;
			iconPosX += compFnd._width + iconSpacing;
		}
		
		itemIcon._visible = true;

		_iconLabel = data.iconLabel != undefined ? data.iconLabel : "default_misc";
		itemIcon.gotoAndStop(_iconLabel);
		itemIcon._width = itemIcon._height = 18;
	}
	
	public function reset(): Void
	{
		dbmNew._visible = false;
		dbmFound._visible = false;
		dbmDisp._visible = false;
		compNew._visible = false;
		compFnd._visible = false;
		itemIcon._visible = false;
		stolenIcon._visible = false;
		enchantIcon._visible = false;
		knownEnchantIcon._visible = false;
		specialEnchantIcon._visible = false;
		readIcon._visible = false;
		itemWeight._visible = false;
		itemValue._visible = false;
		itemValuePerWeight._visible = false;
	}

	// @implements MovieClipLoader
	private function onLoadInit(a_icon: MovieClip): Void
	{
		a_icon.gotoAndStop(_iconLabel);
		itemIcon._width = itemIcon._height = 18;
	}
}
