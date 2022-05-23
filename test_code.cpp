void Generate_pitchtxt()
{
    char byd_name[64];
    char f0_cmd[] = "get_f0.exe -C get_f0.conf -r 0.005 -n 100 -x 500 -g 1 ";
    char wav_name[GENERAL_BUFFER_SIZE], txt_name[GENERAL_BUFFER_SIZE], full_cmd[GENERAL_BUFFER_SIZE];
    for (int j = 0; j < 3; j++)
    {
        if (j == 0) 
            sprintf(byd_name, "XiaoTao");
        else if(j==1) 
            sprintf(byd_name, "XiaoYue");
        else
            sprintf(byd_name, "XiaoYun");
        for (int i = 1; i < 11; i++)
        {
            sprintf(wav_name, "00BYD/BYD_online/BYD_%s_online_%d.wav", byd_name,i); 
            sprintf(txt_name, "00BYD/BYD_online_pitch/BYD_%s_online_%d_pitch.txt", byd_name, i);
            sprintf(full_cmd, "%s%s %s", f0_cmd, wav_name, txt_name);
            system(full_cmd);
            memset(wav_name,' ',sizeof(wav_name));
            memset(txt_name, ' ', sizeof(txt_name));
            memset(full_cmd, ' ', sizeof(full_cmd));

        }
    }
}

SpeakFunction(pIMSSpeechSynthesize, ttsOutputWavFile, MSTTSContentType_SSML, string("00BYD/test.wav"), string("00BYD/audio.txt"));
system("get_f0.exe -C get_f0.conf -r 0.005 -n 100 -x 500 -g 1 00BYD/test.wav 00BYD/test.wav.txt");


MSTTSHANDLE hCSpeechSynthesize;

    UTF_VERIFY_HR(MSTTS_CreateSpeechSynthesizerHandler(&hCSpeechSynthesize));

    UTF_VERIFY_HR(MSTTS_InstallVoices(hCSpeechSynthesize, TestConfig.CustomerVoiceFolder.c_str()));

    // Get installed voices after installing new voices.
    uint32_t nVoiceCount = 0;
    const MSTTSVoiceInfo* pMSVoices = NULL;
    UTF_VERIFY_HR(MSTTS_GetInstalledVoices(hCSpeechSynthesize, &pMSVoices, &nVoiceCount));
    UTF_VERIFY(nVoiceCount > 0);

    // Get the index of speak voice which is defined in config file.
    int nVoiceInfoIndex = -1;
    UTF_VERIFY_HR(TTSTestHelper::GetVoiceInfoIndexByName(nVoiceCount, pMSVoices, TestConfig.CustomerVoiceName, &nVoiceInfoIndex));
    UTF_VERIFY(nVoiceInfoIndex >= 0);

    // Set output format.
    UTF_VERIFY_HR(MSTTS_SetOutput(hCSpeechSynthesize, NULL, ReceiveWaveCallBack, NULL, NULL));

    // Set speak voice.
    UTF_VERIFY_HR(MSTTS_SetVoice(hCSpeechSynthesize, &pMSVoices[nVoiceInfoIndex]));

    string pcszLocaleName = pMSVoices->_pcszLocaleName;
    string test_s;

    string device_xiaotao = "<?xml version=\"1.0\"?>\
			<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\"\
			 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
			 xsi:schemaLocation=\"http://www.w3.org/2001/10/synthesis\
					   http://www.w3.org/TR/speech-synthesis/synthesis.xsd\"\
			 xml:lang= \"" + pcszLocaleName + "\">"
        "<prosody rate='6%' pitch='20%'>" + test_s + "</prosody></speak> ";
    string device_xiaoyue = "<?xml version=\"1.0\"?>\
			<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\"\
			 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
			 xsi:schemaLocation=\"http://www.w3.org/2001/10/synthesis\
					   http://www.w3.org/TR/speech-synthesis/synthesis.xsd\"\
			 xml:lang= \"" + pcszLocaleName + "\">"
        "<prosody rate='16%' pitch='30%'>" + test_s + "</prosody></speak> ";
    string device_xiaoyun = "<?xml version=\"1.0\"?>\
			<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\"\
			 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
			 xsi:schemaLocation=\"http://www.w3.org/2001/10/synthesis\
					   http://www.w3.org/TR/speech-synthesis/synthesis.xsd\"\
			 xml:lang= \"" + pcszLocaleName + "\">"
        "<prosody rate='6%' pitch='-2%'>" + test_s + "</prosody></speak> ";

    ifstream text_file("00BYD/BYD_test_scripts.txt");
    text_file >> test_s;
    cout << test_s;
    device_xiaotao = "<?xml version=\"1.0\"?>\
			<speak version=\"1.0\" xmlns=\"http://www.w3.org/2001/10/synthesis\"\
			 xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
			 xsi:schemaLocation=\"http://www.w3.org/2001/10/synthesis\
					   http://www.w3.org/TR/speech-synthesis/synthesis.xsd\"\
			 xml:lang= \"" + pcszLocaleName + "\">"
        "<prosody rate='6%' pitch='20%'>" + test_s + "</prosody></speak> ";
    SpeakSSML(hCSpeechSynthesize, MSTTSContentType_SSML, "00BYD/BYD_test_scripts.wav", device_xiaotao);
    char* str[1024];
    string s2 = "地震龙";
    cout << s2;

    
   
    if (!text_file)
    {
        cout << "open error!" << endl;
        exit(1);
    }
    char byd_name[64],device_wav_name[GENERAL_BUFFER_SIZE];
    int test_str_count = 0;
    while (!text_file)
    {
        

        test_str_count++;
        for (int i = 0; i < 1; i++)
        {
            if (i == 0)
                sprintf(byd_name, "XiaoTao");
            else if (i == 1)
                sprintf(byd_name, "XiaoYue");
            else
                sprintf(byd_name, "XiaoYun");
            sprintf(device_wav_name, "00BYD/Device/Device_%s_%d.wav", byd_name, test_str_count);
            SpeakSSML(hCSpeechSynthesize, MSTTSContentType_SSML, device_wav_name, device_xiaotao);
        }
    }