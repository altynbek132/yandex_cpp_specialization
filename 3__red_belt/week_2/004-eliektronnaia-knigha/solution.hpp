#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
 public:
  ReadingManager()
  // -1 значит, что не случилось ни одного READ
      : user_page_counts_(MAX_USER_COUNT_ + 1, -1),
        page_achieved_by_count_(MAX_PAGE_COUNT_ + 1, 0) {}
  
  void Read(int user_id, int page_count) {
      UpdatePageRange(user_page_counts_[user_id] + 1, page_count + 1);
      user_page_counts_[user_id] = page_count;
  }
  
  double Cheer(int user_id) const {
      const int pages_count = user_page_counts_[user_id];
      if (pages_count == -1) {
          return 0;
      }
      const int user_count = GetUserCount();
      if (user_count == 1) {
          return 1;
      }
      // По умолчанию деление целочисленное, поэтому
      // нужно привести числитель к типу double.
      // Простой способ сделать это — умножить его на 1.0.
      return (user_count - page_achieved_by_count_[pages_count]) * 1.0
          / (user_count - 1);
  }
 
 private:
  // Статическое поле не принадлежит какому-либо конкретному объекту класса.
  // По сути это глобальная переменная, в данном случае - константная.
  // Будь она публичной, к ней можно было бы обратиться снаружи
  // следующим образом: ReadingManager::MAX_USER_COUNT.
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1'000;
  
  // Номер страницы, до которой дочитал пользователь <ключ>
  vector<int> user_page_counts_;
  // Количество пользователей, дочитавших (как минимум) до страницы <индекс>
  vector<int> page_achieved_by_count_;
  
  int GetUserCount() const {
      return page_achieved_by_count_[0];
  }
  
  // lhs включительно, rhs не включительно
  void UpdatePageRange(int lhs, int rhs) {
      for (int i = lhs; i < rhs; ++i) {
          ++page_achieved_by_count_[i];
      }
  }
};


int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ReadingManager manager;
    
    int query_count;
    cin >> query_count;
    
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;
        
        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    
    return 0;
}
// ===============================================================
// ===============================================================
// ===============================================================
// ===============================================================
// ===============================================================
// ===============================================================

#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>

// Q — количество запросов
// U — максимальный номер пользователя
// P — максимальное значение номера страницы

using namespace std;

class ReadingManager {
 public:
//  U
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, 0),
        sorted_users_(),
        user_positions_(MAX_USER_COUNT_ + 1, -1) {}

// Q*Q
  void Read(int user_id, int page_count) {
      if (user_page_counts_[user_id] == 0) {
          AddUser(user_id);
      }
      user_page_counts_[user_id] = page_count;
      int &position = user_positions_[user_id];
      while (position > 0 && page_count > user_page_counts_[sorted_users_[position - 1]]) {
          SwapUsers(position, position - 1);
      }
  }

//  Q*Q
  double Cheer(int user_id) const {
      if (user_page_counts_[user_id] == 0) {
          return 0;
      }
      const int user_count = GetUserCount();
      if (user_count == 1) {
          return 1;
      }
      const int page_count = user_page_counts_[user_id];
      int position = user_positions_[user_id];
//      U
      while (position < user_count && user_page_counts_[sorted_users_[position]] == page_count) {
          ++position;
      }
      if (position == user_count) {
          return 0;
      }
      return (user_count - position) * 1.0 / (user_count - 1);
  }
 
 private:
  static const int MAX_USER_COUNT_ = 100'000;
  
  vector<int> user_page_counts_;
  vector<int> sorted_users_;  // отсортированы по убыванию
  // количества страниц
  vector<int> user_positions_;  // позиции в векторе sorted_users_
  
  int GetUserCount() const {
      return sorted_users_.size();
  }

//  1
  void AddUser(int user_id) {
      sorted_users_.push_back(user_id);
      user_positions_[user_id] = sorted_users_.size() - 1;
  }
  
  void SwapUsers(int lhs_position, int rhs_position) {
      const int lhs_id = sorted_users_[lhs_position];
      const int rhs_id = sorted_users_[rhs_position];
      swap(sorted_users_[lhs_position], sorted_users_[rhs_position]);
      swap(user_positions_[lhs_id], user_positions_[rhs_id]);
  }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ReadingManager manager;
    
    int query_count;
    cin >> query_count;
    
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;
        
        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    
    return 0;
}
// ===============================================================
// ===============================================================
// ===============================================================
// ===============================================================
// ===============================================================
// ===============================================================
#include <vector>
#include <utility>
#include <map>

using namespace std;

class ReadingManager {
 public:
//  U + P
  ReadingManager()
      : user_page_counts_(MAX_USER_COUNT_ + 1, -1),
        page_achieved_by_count_(MAX_PAGE_COUNT_ + 1, 0) {}

//  UP + Q
  void Read(int user_id, int page_count) {
//      UP
      UpdatePageRange(user_page_counts_[user_id] + 1, page_count + 1);
      user_page_counts_[user_id] = page_count;
  }

//  Q
  double Cheer(int user_id) const {
      const int pages_count = user_page_counts_[user_id];
      if (pages_count == -1) {
          return 0;
      }
      const int user_count = GetUserCount();
      if (user_count == 1) {
          return 1;
      }
      return (user_count - page_achieved_by_count_[pages_count]) * 1.0
          / (user_count - 1);
  }
 
 private:
  static const int MAX_USER_COUNT_ = 100'000;
  static const int MAX_PAGE_COUNT_ = 1'000;
  
  vector<int> user_page_counts_;
  vector<int> page_achieved_by_count_;
  
  int GetUserCount() const {
      return page_achieved_by_count_[0];
  }
  
  void UpdatePageRange(int lhs, int rhs) {
      for (int i = lhs; i < rhs; ++i) {
          ++page_achieved_by_count_[i];
      }
  }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ReadingManager manager;
    
    int query_count;
    cin >> query_count;
    
    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;
        
        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }
    
    return 0;
}