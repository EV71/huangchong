//****************************************
//��������������ComboBox������Ŀ�ı���ͼ��
//���ߣ�    �⺣��
//���ڣ�    2011-01-26
//****************************************
using System;
using System.Collections.Generic;
using System.Text;

namespace ComboBoxEx
{
    public class ImageComboBoxItem
    {
        //�����ı�����
        private string _text;
        public string Text
        {
        get {return _text;}
        set {_text = value;}
        }
        //����ͼ����������
        private int _imageIndex;
        public int ImageIndex
        {
        get {return _imageIndex;}
        set {_imageIndex = value;}
        }
        //��ʼ������֮һ����û��ͼ��Ҳû���ı�
        public ImageComboBoxItem():this("",-1) 
        {
        }
        //��ʼ������֮����û��ͼ��ֻ���ı�
        public ImageComboBoxItem(string text): this(text, -1) 
        {
        }
        //��ʼ������֮�����ı���ͼ����
        public ImageComboBoxItem(string text, int imageIndex)
        {
        _text = text;
        _imageIndex = imageIndex;
        }

        public override string ToString()
        {
        return _text;
        }
    }
}
