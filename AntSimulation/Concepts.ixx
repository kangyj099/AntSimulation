export module concepts;

import <type_traits>;

import component;

/// <summary>
/// 컴포넌트 베이스를 상속받은 컴포넌트 클래스로 템플릿 제한
/// </summary>
export template<typename T>
concept ComponentDerived = std::is_base_of_v<ComponentBase, T>;