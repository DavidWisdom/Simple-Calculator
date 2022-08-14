#include "calculator.h"
#include <QGraphicsDropShadowEffect>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);    // 禁止最大化按钮
    setFixedSize(this->width(), this->height());                     // 禁止拖动窗口大小
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    setFixedSize(this->width(), this->height());
    //setAttribute(Qt::WA_TranslucentBackground);
}

QString Calculator::showQString(const QString& qstr)
{
	// int begin = 0;
	// int end = qstr.size();
	// QString res;
	// while (end > begin) {
	// 	int start = std::max(begin, end);
	// 	QString tmp = qstr.mid(start, end - start);
	// 	res += tmp + ',';
	// 	end -= 3;
	// }
	// return res.left(res.size() - 1);
	int begin = 0;
	QString res = qstr;
	int end = res.size();
	while (end > begin)
	{
		int start = std::max(begin, end - 3);
		res.insert(start, ',');
		end -= 3;
	}
	return res.right(res.size() - 1);
}

void Calculator::push(const char c)
{
	switch (cur)
	{
	case 1:
		{
			if (!isVal1HasDot)
			{
				if (isVal1Empty)
				{
					val1 = c;
					isVal1Empty = false;
				}
				else
				{
					val1 = val1 + c;
				}
				if (symbolOfVal1 || isVal1Empty)
				{
					ui.lineEdit->setText(showQString(val1));
				}
				else
				{
					ui.lineEdit->setText('-' + showQString(val1));
				}
			}
			else
			{
				QString text = ui.lineEdit->text();
				ui.lineEdit->setText(text + c);
			}
		}
		break;
	case 2:
		{
			if (!isVal2HasDot)
			{
				if (isVal2Empty)
				{
					val2 = c;
					isVal2Empty = false;
				}
				else
				{
					val2 = val2 + c;
				}
				if (symbolOfVal2 || isVal2Empty)
				{
					ui.lineEdit->setText(showQString(val2));
				}
				else
				{
					ui.lineEdit->setText('-' + showQString(val2));
				}
			}
			else
			{
				QString text = ui.lineEdit->text();
				ui.lineEdit->setText(text + c);
			}
		}
		break;
	default:
		break;
	}
}

void Calculator::on_pushButton_1_clicked()
{
	push('1');
}

void Calculator::on_pushButton_2_clicked()
{
	push('2');
}

void Calculator::on_pushButton_3_clicked()
{
	push('3');
}

void Calculator::on_pushButton_4_clicked()
{
	push('4');
}

void Calculator::on_pushButton_5_clicked()
{
	push('5');
}

void Calculator::on_pushButton_6_clicked()
{
	push('6');
}

void Calculator::on_pushButton_7_clicked()
{
	push('7');
}

void Calculator::on_pushButton_8_clicked()
{
	push('8');
}

void Calculator::on_pushButton_9_clicked()
{
	push('9');
}
void Calculator::on_pushButton_10_clicked()
{
	switch (cur)
	{
	case 1:
	{
		if (!isVal1HasDot)
		{
			if (isVal1Empty)
			{
				val1 = '0';
			}
			else
			{
				val1 = val1 + '0';
			}
			if (symbolOfVal1 || isVal1Empty)
			{
				ui.lineEdit->setText(showQString(val1));
			}
			else
			{
				ui.lineEdit->setText('-' + showQString(val1));
			}
		}
		else
		{
			QString text = ui.lineEdit->text();
			ui.lineEdit->setText(text + '0');
		}
	}
	break;
	case 2:
	{
		if (!isVal2HasDot)
		{
			if (isVal2Empty)
			{
				val2 = '0';
			}
			else
			{
				val2 = val2 + '0';
			}
			if (symbolOfVal2 || isVal2Empty)
			{
				ui.lineEdit->setText(showQString(val2));
			}
			else
			{
				ui.lineEdit->setText('-' + showQString(val2));
			}
		}
		else
		{
			QString text = ui.lineEdit->text();
			ui.lineEdit->setText(text + '0');
		}
	}
	break;
	default:
		break;
	}
}
void Calculator::on_pushButton_11_clicked()
{
	switch(cur)
	{
	case 1:
		{
			if (isVal1HasDot)
			{
				break;
			}
			{
				QString text = ui.lineEdit->text();
				ui.lineEdit->setText(text + '.');
				isVal1HasDot = true;
			}
		}
		break;
	case 2:
		{
			if (isVal2HasDot)
			{
				break;
			}
			{
				QString text = ui.lineEdit->text();
				ui.lineEdit->setText(text + '.');
				isVal2HasDot = true;
			}
		}
		break;
	default:
		break;
	}
}
void Calculator::on_pushButton_12_clicked()
{
	val1 = ui.lineEdit->text();
	cur = 2;
	isVal2Empty = true;
	symbolOfVal2 = true;
	isVal2HasDot = false;
	val2.clear();
	ui.lineEdit->setText(QString('0'));
	ch = '+';
	isCh = true;
}
void Calculator::on_pushButton_13_clicked()
{
	val1 = ui.lineEdit->text();
	cur = 2;
	isVal2Empty = true;
	symbolOfVal2 = true;
	isVal2HasDot = false;
	val2.clear();
	ui.lineEdit->setText(QString('0'));
	ch = '-';
	isCh = true;
}
void Calculator::on_pushButton_14_clicked()
{
	val1 = ui.lineEdit->text();
	cur = 2;
	isVal2Empty = true;
	symbolOfVal2 = true;
	isVal2HasDot = false;
	val2.clear();
	ui.lineEdit->setText(QString('0'));
	ch = '*';
	isCh = true;
}
void Calculator::on_pushButton_15_clicked()
{
	val1 = ui.lineEdit->text();
	cur = 2;
	isVal2Empty = true;
	symbolOfVal2 = true;
	isVal2HasDot = false;
	val2.clear();
	ui.lineEdit->setText(QString('0'));
	ch = '/';
	isCh = true;
}
void Calculator::on_pushButton_16_clicked()
{
	if (isCh)
	{
	val2 = ui.lineEdit->text();
	BigNumber::BigDecimal bigDecimal1(val1.toStdString());
	BigNumber::BigDecimal bigDecimal2(val2.toStdString());
	BigNumber::BigDecimal res;
	QString text;
	try
	{
			switch(ch)
			{
			case '+':
				{
					res = bigDecimal1 + bigDecimal2;
					std::string ans = res;
					text = text.fromStdString(ans);
					ui.lineEdit->setText(text);
				}
				break;
			case '-':
				{
					res = bigDecimal1 - bigDecimal2;
					std::string ans = res;
					text = text.fromStdString(ans);
					ui.lineEdit->setText(text);
				}
				break;
			case '*':
				{
					res = bigDecimal1 * bigDecimal2;
					std::string ans = res;
					text = text.fromStdString(ans);
					ui.lineEdit->setText(text);
				}
				break;
			case '/':
				{
					res = bigDecimal1 / bigDecimal2;
					std::string ans = res.round();
					text = text.fromStdString(ans);
					ui.lineEdit->setText(text);
				}
				break;
			default:
				break;
			}
			val1 = ui.lineEdit->text();
			isVal1Empty = true;
			cur = 1;
			isCh = false;
	}
		catch(...)
		{
		ui.lineEdit->setText("ERROR");
		val1 = "0";
		isVal1Empty = true;
		cur = 1;
		isCh = false;
		}
	}
}
void Calculator::on_pushButton_17_clicked()
{
	switch(cur)
	{
	case 1:
		{
			if (symbolOfVal1)
			{
				if (!isVal1Empty)
				{
					QString text = ui.lineEdit->text();
					ui.lineEdit->setText('-' + text);
					symbolOfVal1 = !symbolOfVal1;
				}
			}
			else
			{
				QString text = ui.lineEdit->text();
				ui.lineEdit->setText(text.right(text.size() - 1));
				symbolOfVal1 = !symbolOfVal1;
			}
		}
		break;
	case 2:
		{
			if (symbolOfVal2)
			{
				if (!isVal2Empty)
				{
					QString text = ui.lineEdit->text();
					ui.lineEdit->setText('-' + text);
					symbolOfVal2 = !symbolOfVal2;
				}
			}
			else
			{
				QString text = ui.lineEdit->text();
				ui.lineEdit->setText(text.right(text.size() - 1));
				symbolOfVal2 = !symbolOfVal2;
			}
		}
		break;
	default:
		break;
	}
}
// void Calculator::on_pushButton_17_clicked()
// {
// 	if (symbol) {
// 		if (!isEmpty)
// 		{
// 			QString text = ui.lineEdit->text();
// 			ui.lineEdit->setText('-' + text);
// 			symbol = !symbol;
// 		}
// 	}
// 	else
// 	{
// 		QString text = ui.lineEdit->text();
// 		ui.lineEdit->setText(text.right(text.size() - 1));
// 		symbol = !symbol;
// 	}
// }
void Calculator::on_pushButton_18_clicked()
{
	switch(cur)
	{
	case 1:
		{
			
		}
		break;
	case 2:
		break;
	}
}
void Calculator::on_pushButton_19_clicked()
{
	ui.lineEdit->setText(QString('0'));
	isVal1Empty = true;
	symbolOfVal1 = true;
	isVal1HasDot = false;
	isVal2Empty = true;
	symbolOfVal2 = true;
	isVal2HasDot = false;
	cur = 1;
}
void Calculator::on_pushButton_20_clicked()
{
	switch (cur)
	{
	case 1:
		{
			ui.lineEdit->setText(QString('0'));
			isVal1Empty = true;
			symbolOfVal1 = true;
			isVal1HasDot = false;
		}
		break;
	case 2:
		{
			ui.lineEdit->setText(QString('0'));
			isVal2Empty = true;
			symbolOfVal2 = true;
			isVal2HasDot = false;
		}
		break;
	default:
		break;
	}

}
// void Calculator::push(const char c)
// {
// 	
// }
//
// void Calculator::on_pushButton_1_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('1'));
// 		isEmpty = false;
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '1');
// }
//
// void Calculator::on_pushButton_2_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('2'));
// 		isEmpty = false;
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '2');
// }
//
// void Calculator::on_pushButton_3_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('3'));
// 		isEmpty = false;
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '3');
// }
//
// void Calculator::on_pushButton_4_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('4'));
// 		isEmpty = false;
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '4');
// }
//
// void Calculator::on_pushButton_5_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('5'));
// 		isEmpty = false;
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '5');
// }
//
// void Calculator::on_pushButton_6_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('6'));
// 		isEmpty = false;
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '6');
// }
//
// void Calculator::on_pushButton_7_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('7'));
// 		isEmpty = false;
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '7');
// }
//
// void Calculator::on_pushButton_8_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('8'));
// 		isEmpty = false;
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '8');
// }
//
// void Calculator::on_pushButton_9_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('9'));
// 		isEmpty = false;
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '9');
// }
//
// void Calculator::on_pushButton_10_clicked()
// {
// 	if (isEmpty)
// 	{
// 		ui.lineEdit->setText(QString('0'));
// 		return;
// 	}
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '0');
// }
//
// void Calculator::on_pushButton_11_clicked()
// {
// 	QString text = ui.lineEdit->text();
// 	ui.lineEdit->setText(text + '.');
// }
//
// void Calculator::on_pushButton_12_clicked()
// {
// 	QString text = ui.lineEdit->text();
// 	str1 = text.toStdString();
// 	c = '+';
// 	isEmpty = true;
// 	ui.lineEdit->setText(QString('0'));
// }
//
// void Calculator::on_pushButton_13_clicked()
// {
// 	QString text = ui.lineEdit->text();
// 	str1 = text.toStdString();
// 	c = '-';
// 	isEmpty = true;
// 	ui.lineEdit->setText(QString('0'));
// }
//
// void Calculator::on_pushButton_14_clicked()
// {
// 	QString text = ui.lineEdit->text();
// 	str1 = text.toStdString();
// 	c = '*';
// 	isEmpty = true;
// 	ui.lineEdit->setText(QString('0'));
// }
//
// void Calculator::on_pushButton_15_clicked()
// {
// 	QString text = ui.lineEdit->text();
// 	str1 = text.toStdString();
// 	c = '/';
// 	isEmpty = true;
// 	ui.lineEdit->setText(QString('0'));
// }
//
// void Calculator::on_pushButton_16_clicked()
// {
// 	QString text = ui.lineEdit->text();
// 	str2 = text.toStdString();
// 	BigNumber::BigDecimal bigDecimal1(str1, false);
// 	BigNumber::BigDecimal bigDecimal2(str2, false);
// 	BigNumber::BigDecimal res;
// 	switch(c)
// 	{
// 	case '+':
// 		{
// 			res = bigDecimal1 + bigDecimal2;
// 			std::string ans = res;
// 			text = text.fromStdString(ans);
// 			ui.lineEdit->setText(text);
// 		}
// 		break;
// 	case '-':
// 		{
// 			res = bigDecimal1 - bigDecimal2;
// 			std::string ans = res;
// 			text = text.fromStdString(ans);
// 			ui.lineEdit->setText(text);
// 		}
// 		break;
// 	case '*':
// 		{
// 			res = bigDecimal1 * bigDecimal2;
// 			std::string ans = res;
// 			text = text.fromStdString(ans);
// 			ui.lineEdit->setText(text);
// 		}
// 		break;
// 	case '/':
// 		{
// 			res = bigDecimal1 / bigDecimal2;
// 			std::string ans = res.round();
// 			text = text.fromStdString(ans);
// 			ui.lineEdit->setText(text);
// 		}
// 		break;
// 	default:
// 		break;
// 	}
// 	isEmpty = true;
// }
//
// void Calculator::on_pushButton_17_clicked()
// {
// 	if (symbol) {
// 		if (!isEmpty)
// 		{
// 			QString text = ui.lineEdit->text();
// 			ui.lineEdit->setText('-' + text);
// 			symbol = !symbol;
// 		}
// 	}
// 	else
// 	{
// 		QString text = ui.lineEdit->text();
// 		ui.lineEdit->setText(text.right(text.size() - 1));
// 		symbol = !symbol;
// 	}
// }
//
// void Calculator::on_pushButton_18_clicked()
// {
// 	QString text = ui.lineEdit->text();
// 	if (text.size() == 1) isEmpty = true;
// 	ui.lineEdit->setText(text.left(text.size() - 1));
// }
//
// void Calculator::on_pushButton_19_clicked()
// {
// 	
// }
//
// void Calculator::on_pushButton_20_clicked()
// {
// 	isEmpty = true;
// 	ui.lineEdit->setText(QString('0'));
// }

