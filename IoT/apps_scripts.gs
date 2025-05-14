function doGet(e) { 
  Logger.log(JSON.stringify(e));
  var result = 'Ok';
  if (e.parameter == 'undefined') {
    result = 'No Parameters';
  }
  else {
    var sheet_id = '16RyCx87am3_8CClYv7zRZYxe54shnyrsgnswWFfaewi-DWSM'; 	// Spreadsheet ID.
    var sheet_name = "ESP32_Google_Sheets_Sheet";  // Sheet Name in Google Sheets.

    var sheet_open = SpreadsheetApp.openById(sheet_id);
    var sheet_target = sheet_open.getSheetByName(sheet_name);

    var newRow = sheet_target.getLastRow() + 1;

    var rowDataLog = [];

    var Data_for_I3;
    var Data_for_J3;
    var Data_for_K3;
    var Data_for_L3;
    var Data_for_M3;
    var Data_for_N3;
    var Data_for_O3;

    var Curr_Date = Utilities.formatDate(new Date(), "Asia/Jakarta", 'dd/MM/yyyy');
    rowDataLog[0] = Curr_Date; 
    Data_for_I3 = Curr_Date; 
    var Curr_Time = Utilities.formatDate(new Date(), "Asia/Jakarta", 'HH:mm:ss');
    rowDataLog[1] = Curr_Time;  
    Data_for_J3 = Curr_Time;  

    var sts_val = '';

    for (var param in e.parameter) {
      Logger.log('In for loop, param=' + param);
      var value = stripQuotes(e.parameter[param]);
      Logger.log(param + ':' + e.parameter[param]);
      switch (param) {
        case 'sts':
          sts_val = value;
          break;

        case 'srs':
          rowDataLog[2] = value; 
          Data_for_K3 = value; 
          result += ', Sensor Reading Status Written on column C';
          break;

        case 'temp':
          rowDataLog[3] = value; 
          Data_for_L3 = value;  
          result += ', Temperature Written on column D';
          break;

        case 'humd':
          rowDataLog[4] = value; 
          Data_for_M3 = value; 
          result += ', Humidity Written on column E';
          break;

        case 'swtc1':
          rowDataLog[5] = value;
          Data_for_N3 = value; 
          result += ', Switch_1 Written on column F';
          break;

        case 'swtc2':
          rowDataLog[6] = value;  
          Data_for_O3 = value;
          result += ', Switch_2 Written on column G';
          break;  

        default:
          result += ", unsupported parameter";
      }
    }
    
    // Conditions for writing data received from ESP32 to Google Sheets.
    if (sts_val == 'write') {
      Logger.log(JSON.stringify(rowDataLog));
      var newRangeDataLog = sheet_target.getRange(newRow, 1, 1, rowDataLog.length);
      newRangeDataLog.setValues([rowDataLog]);
      
      // Write the data to the "Latest DHT11 Sensor Data" section.
      var RangeDataLatest = sheet_target.getRange('I3:O3');
      RangeDataLatest.setValues([[Data_for_I3, Data_for_J3, Data_for_K3, Data_for_L3, Data_for_M3, Data_for_N3, Data_for_O3]]);

      return ContentService.createTextOutput(result);
    }
   
    if (sts_val == 'read') {
      var all_Data = sheet_target.getRange('K3:O3').getValues();
      return ContentService.createTextOutput(all_Data);
    }
  }
}
function stripQuotes( value ) {
  return value.replace(/^["']|['"]$/g, "");
}
